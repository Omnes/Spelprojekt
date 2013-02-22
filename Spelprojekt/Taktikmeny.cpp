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

	for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
		if((*i)->getAfraidAnimal()){

			(*i)->getPrototypeAnimal()->setExtraSpeed(2.0f);

		}
	}

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
						for(SpotVector::size_type k = 0; k < mSpotVector.size(); ++k){
							int level = mSpotVector[k]->getLevel();
							//om positionen på nummret i speedvectorn är detsamma som spottens position
						

							if(mSpotVector[k]->getPrototypeAnimal() != 0 && (k+1) < mSpotVector.size() && level == j){

								////rovdjur VS växtätare
								if(mSpotVector[k]->getPrototypeAnimal()->getAnimalType() == "meat" && mSpotVector[k+1]->getLevel() == mSpotVector[k]->getLevel() && mCurrentDragAnimal->getAnimalType() == "plant" /*&& mSpotVector[i]->getColorSpot() != 2*/          /*snabbaste farten är == 2*/){
									//aktiviera ljus
									mSpotVector[k+1]->setActSpot(true);
									mSpotVector[k+1]->setColorSpot(2);

									//rovdjuret får också speed. inte bra
									//mSpotVector[k+1]->setAfraidAnimal(true);
								}
							
							}


							if(level == j && mSpotVector[k]->getPrototypeAnimal() == 0 && mCurrentDragAnimal->getLevel() != level && mSpotVector[k]->getColorSpot() != 2/*<--funkar inte egentligen*/){

								//aktiviera ljus
								mSpotVector[k]->setActSpot(true);
								mSpotVector[k]->setColorSpot(1);
								//mSpotVector[k]->setAfraidAnimal(false);

							}else if(mCurrentDragAnimal->getLevel() == level && mSpotVector[k]->getPrototypeAnimal() == 0){
								
								//aktiviera ljus snabbt
								mSpotVector[k]->setActSpot(true);
								mSpotVector[k]->setColorSpot(2);
								//mSpotVector[k]->setAfraidAnimal(false);

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
				for(SpotVector::size_type j = 0; j < mSpotVector.size(); j++){
					int level = mSpotVector[j]->getLevel();
					//om positionen på nummret i speedvectorn är detsamma som spottens position
					if(level == i && mCurrentDragAnimal != 0){
						if(mSpotVector[j]->getActSpot() == true && mSpotVector[j]->getTakenSpot() == false && mCurrentDragAnimal->getSprite()->getGlobalBounds().intersects(mSpotVector[j]->getSprite()->getGlobalBounds())){
							mCurrentDragAnimal->setPos(mSpotVector[j]->getSprite()->getPosition());
							mCurrentDragAnimal->setStandardSpeed(mSpeedVector[i]);
							
							//här är pekarsatsen
							mSpotVector[j]->setPrototypeAnimal(mCurrentDragAnimal);
							mSpotVector[j]->setTakenSpot(true);

							//out of boundsgrej. assertsats typ
							if(mSpotVector[j]->getPrototypeAnimal() != 0 && (j+1) < mSpotVector.size() && level == i){
								////rovdjur VS växtätare
								if(mSpotVector[j]->getPrototypeAnimal()->getAnimalType() == "meat" && mSpotVector[j+1]->getLevel() == mSpotVector[j]->getLevel() /*&& mSpotVector[j+1]->getPrototypeAnimal()->getAnimalType() == "plant"*/  /* && mSpotVector[j]->getColorSpot() != 2*/){ //<---------------------- HÄR KOLLLA ROBINTNTNTTNTNNT
									
									
									
									
									
									
									//xstring size är för kort. 	gillar ej: mSpotVector[j+1]->getPrototypeAnimal()->getAnimalType() == "plant"				
//HÄRÄRÄÄRÄR
//HÄRÄRÄÄRÄR

//HÄRÄRÄÄRÄR
//HÄRÄRÄÄRÄR
									//HÄRÄRÄÄRÄR
									
									
									
									
									
									mSpotVector[j]->setAfraidAnimal(true);
								}
							}

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

