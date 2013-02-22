#include "Taktikmeny.h"
#include "WindowManager.h"
#include "LevelManager.h"
#include "Spot.h"
#include "AnimalPrototype.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "TacticMenuButton.h"

#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window\Keyboard.hpp>

TaktikMeny::TaktikMeny() : 
	mCurrentDragAnimal(0),
	mLevelTop(0),
	mLevelMiddle(0),
	mLevelGround(0),
	mAllSpotsTaken(false)
{
	mButton = new TacticMenuButton(sf::Vector2f(500,600), this, "Resources/Menu/TacticMenu/startgameplaybutton.png", "Resources/Sound/test.wav");

	mAnimalSpriteBg.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/TacticMenu/taktikdjurbg.png"));
	mAnimalSpriteBg.setPosition(550, 0);

	LevelManager::getInst().preloadBackgrounds();

	readFromFile();
	receiveAnimals();
	placeSpots();

	mMusic = "Resources/Sound/TitleScreen";

}

TaktikMeny::~TaktikMeny(){

	while(mSpotVector.size() != 0){
		delete mSpotVector.back();
		mSpotVector.pop_back();
	}

	while(mFakeAnimals.size() != 0){
		delete mFakeAnimals.back();
		mFakeAnimals.pop_back();
	}

	delete mButton;
}


void TaktikMeny::update(){

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		isClicked();
	}else{
		isNotClicked();
	}

	mButton->update();
}

void TaktikMeny::render(){

	sf::RenderWindow *window = WindowManager::getInst().getWindow();


	for(BgVector::iterator i = mBgVector.begin(); i != mBgVector.end(); i++){
		window->draw((*i));
	}

	window->draw(mAnimalSpriteBg);

	for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
		window->draw(*(*i)->getSprite());
	}

	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); i++){
		window->draw(*(*i)->getSprite());
	}

	window->draw(mButton->getSprite());

}


//tar emot och placerar ut animaler innan de kan placeras
void TaktikMeny::receiveAnimals(){

	sf::RenderWindow *window = WindowManager::getInst().getWindow();

	int minDist = 600;

	sf::Vector2f startPos = sf::Vector2f(window->getSize().x - minDist,128);
	sf::Vector2f distance = sf::Vector2f(128,128);
	mFakeAnimals = LevelManager::getInst().getAnimalsOnLevel();

	int counter = 0;

	for(int y = 0;counter < mFakeAnimals.size(); y++){
		for(int x = 0;x < 4;x++){
			mFakeAnimals[counter]->setPos(startPos + sf::Vector2f(distance.x*x, distance.y*y));
			mFakeAnimals[counter]->setStartPos(startPos + sf::Vector2f(distance.x*x, distance.y*y));
			counter ++;
			if(counter >= mFakeAnimals.size())
				return;

		}
	}



}

void TaktikMeny::placeSpots(){
	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); i++){
		//hämtar var alla olika prototypeanimals ska ligga. och lägger de i en vektor
		//ska sedan kolla igenom vektorn och räkna hur många olika platser det är på varje.
		mLevelVector.push_back((*i)->getLevel());
	}

	//sätter hur många platser det finns per nivå ground/middle/top
	for(LevelVector::iterator i = mLevelVector.begin(); i != mLevelVector.end(); i++){
		if((*i) == 0){
			mLevelTop++;
		}else if((*i) == 1){
			mLevelMiddle++;
		}else{
			mLevelGround++;
		}
	}

	//flyttar ner spots från toppen till ground
	mLevelGround += mLevelTop / 2;
	mLevelTop = ((float)mLevelTop / 2) + 0.5;

	mPosVector.push_back(mLevelTop);
	mPosVector.push_back(mLevelMiddle);
	mPosVector.push_back(mLevelGround); // värdelöst ???

	int xDistance = 128;
	int startX = 80;

	std::vector<float> LevelYVector = LevelManager::getInst().getLevelsOnLevel();

	//placerar ut spots 
	for(std::vector<float>::size_type i = 0; i < LevelYVector.size(); i++){
		for(int j = 0; j < mPosVector[i]; j++){
			mSpotVector.push_back(new Spot(i, sf::Vector2f(startX + j*xDistance, LevelYVector[i])));
		}
	}
}


void TaktikMeny::createAnimals(){

	//setSpeed();

	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); ++i){
		mAnimalVector.push_back((Entity*)(*i)->createAnimal());
	}

	LevelManager::getInst().setAnimalPosition(mAnimalVector);
}

void TaktikMeny::isClicked(){
	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

		if(mCurrentDragAnimal == 0){

			for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); ++i){
				if((*i)->getSprite()->getGlobalBounds().contains(mousePosition)){
					mCurrentDragAnimal = (*i);
					mCurrentDragAnimal->playSound();
					mCurrentDragAnimal->getSprite()->setScale(0.8,0.8);
					mGrabOffset = mCurrentDragAnimal->getPos() - mousePosition;
				}
			}


			//kan fucka ur om man tar djur utanför spotboxen
			for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
				if((*i)->getPrototypeAnimal() == mCurrentDragAnimal){
					(*i)->setTakenSpot(false);
				}
			}

			if(mCurrentDragAnimal != 0){
				mSpeedVector = mCurrentDragAnimal->getSpeedVector();
				//går igenom animal speedvector som innehåller tre olika hastigheteter
				for(SpeedVector::size_type j = 0; j < mSpeedVector.size(); j++){
					//om speedvector inte har ngn nolla i sig
					if(mSpeedVector[j] != 0){
						//går igenom de olika spotsen
						for(SpotVector::iterator k = mSpotVector.begin(); k != mSpotVector.end(); k++){
							int level = (*k)->getLevel();
							//om positionen på nummret i speedvectorn är detsamma som spottens position
							if(level == j && (*k)->getPrototypeAnimal() == 0){
								if(mCurrentDragAnimal->getLevel() != level){
									//aktiviera ljus
									(*k)->setActSpot(true);
									(*k)->setColorSpot(1);
								}else{
									//aktiviera ljus snabb
									(*k)->setActSpot(true);
									(*k)->setColorSpot(2);
								}
							}
						}
					}
				}
			}

		}

		if(mCurrentDragAnimal !=0){
			float floatSpeed = 0.75;
			mGrabOffset.x *= floatSpeed;
			mGrabOffset.y *= floatSpeed;
			mCurrentDragAnimal -> setPos(mousePosition + mGrabOffset);
		}

}

void TaktikMeny::isNotClicked(){

	//om mCurrentAnimal är över en spot
	if(mCurrentDragAnimal != 0){
		mCurrentDragAnimal->getSprite()->setScale(1,1);
		mSpeedVector = mCurrentDragAnimal->getSpeedVector();

		for(SpeedVector::size_type i = 0; i < mSpeedVector.size(); i++){
			//om speedvector inte har ngn nolla i sig
			if(mSpeedVector[i] != 0){
				//går igenom de olika spotsen
				for(SpotVector::iterator j = mSpotVector.begin(); j != mSpotVector.end(); j++){
					int level = (*j)->getLevel();
					//om positionen på nummret i speedvectorn är detsamma som spottens position
					if(level == i && mCurrentDragAnimal != 0){
						if((*j)->getActSpot() == true && (*j)->getTakenSpot() == false && mCurrentDragAnimal->getSprite()->getGlobalBounds().intersects((*j)->getSprite()->getGlobalBounds())){
							mCurrentDragAnimal->setPos((*j)->getSprite()->getPosition());
							mCurrentDragAnimal->setStandardSpeed(mSpeedVector[i]);
							
							//här är pekarsatsen
							(*j)->setPrototypeAnimal(mCurrentDragAnimal);

							(*j)->setTakenSpot(true);

							mCurrentDragAnimal = 0;

						}
					}
				}
			}
		}
		if(mCurrentDragAnimal != 0){
			mCurrentDragAnimal->setPos(mCurrentDragAnimal->getStartPos());
		}
		
		mCurrentDragAnimal = 0;

		for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
			if((*i)->getTakenSpot() == false){
				(*i)->setPrototypeAnimal(0);
				(*i)->setActSpot(false);
				(*i)->setColorSpot(0);
			}
		}

	}

}

void TaktikMeny::readFromFile(){
	tinyxml2::XMLDocument doc;

	doc.LoadFile(LevelManager::getInst().getFilePath().c_str());

	tinyxml2::XMLElement* elem = doc.FirstChildElement()->FirstChildElement();

	while (elem != 0){
		std::string layerType = elem->FirstChildElement("Layer")->GetText();
		if(layerType == "static"){
			const tinyxml2::XMLElement *img = elem->FirstChildElement("Images")->FirstChildElement();
			sf::Sprite bg(*ResourceManager::getInst().getTexture(img->GetText()));
			bg.setPosition(0,0);
			mBgVector.push_back(bg);
		}
		elem = elem->NextSiblingElement();
	}
}

std::string TaktikMeny::getMusic(){
	return mMusic;
}

bool TaktikMeny::getFreeSpots(){

	bool freeSpots = false;

	for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
		if((*i)->getPrototypeAnimal() == 0){
			freeSpots = true;
		}
	}

	return freeSpots;
}

void TaktikMeny::setSpeed(){
	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); ++i){
		
	}
}