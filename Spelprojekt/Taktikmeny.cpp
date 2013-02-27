#include "Taktikmeny.h"
#include "WindowManager.h"
#include "LevelManager.h"
#include "Spot.h"
#include "AnimalPrototype.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "TacticMenuButton.h"
#include "FakeAbilityButton.h"

#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <cmath>

TaktikMeny::TaktikMeny() : 
	mCurrentDragAnimal(0),
	mLevelTop(0),
	mLevelMiddle(0),
	mLevelGround(0),
	mAllSpotsTaken(false)
{
	mButton = new TacticMenuButton(sf::Vector2f(950,635), this, "Resources/Menu/TacticMenu/startgameplaybutton.png", "Resources/Sound/test.wav");
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

	for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
		(*i)->update();
	}


	mButton->update();

	for(std::vector<FakeAbilityButton*>::iterator i = mAbilityButtons.begin(); i != mAbilityButtons.end(); i++){
		(*i)->update();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		EventManager::getInst().addEvent("popState");

	}
}

void TaktikMeny::render(){


	sf::RenderWindow *window = WindowManager::getInst().getWindow();
		

	for(BgVector::iterator i = mBgVector.begin(); i != mBgVector.end(); i++){
		window->draw((*i));
	}


	window->draw(mAnimalSpriteBg);
	
	window->draw(mGui);

	for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
		window->draw(*(*i)->getSprite());
	}

	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); i++){
		window->draw(*(*i)->getSprite());
	}

	window->draw(mButton->getSprite());

	for(std::vector<FakeAbilityButton*>::iterator i = mAbilityButtons.begin(); i != mAbilityButtons.end(); i++){
		(*i)->render();
	}

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
			(*i)->getPrototypeAnimal()->setExtraSpeed(4.0f);
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
					break;
				}
			}

			for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
				if((*i)->getPrototypeAnimal() == mCurrentDragAnimal){
					(*i)->setPrototypeAnimal(0);
					(*i)->setAfraidAnimal(false);
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
						
							if(level == j){
								//if rovdjur är nertrycck, kolla igenom spots efter plant/växtdjur
								if(k >= 1){ // eh ??? k > 2 osäker här, fösrta argumentet kommer aldrig hända pga. man hinner inte klicka innan den laddat allt
									if(mSpotVector[k]->getPrototypeAnimal() != 0){
										if(mCurrentDragAnimal->getAnimalType() == "meat" && mSpotVector[k]->getPrototypeAnimal()->getAnimalType()== "plant" && mSpotVector[k-1]->getPrototypeAnimal() == 0 && mSpotVector[k-1]->getLevel() == mSpotVector[k]->getLevel()){
											mSpotVector[k]->setColorSpot(sf::Color(255,0,0,255)); //fixa detta ? kanske
										}
									}
								}

								mSpotVector[k]->setActSpot(true);

								//går igenom spotvectorn och kollar efter rovdjur
								//gör detta till en funktion
								if(level == j && mSpotVector[k]->getPrototypeAnimal() != 0 && (k+1) < mSpotVector.size()){
									if(mSpotVector[k]->getPrototypeAnimal()->getAnimalType() == "meat" && mSpotVector[k+1]->getLevel() == mSpotVector[k]->getLevel() && mCurrentDragAnimal->getAnimalType() == "plant" && mSpotVector[k+1]->getPrototypeAnimal() == 0/*och maxhastifghetinte är uppnådd*/){
										mSpotVector[k+1]->setColorSpot(sf::Color(255,0,0,255)); //fixa detta ? kanske
										mSpotVector[k+1]->setAfraidAnimal(true);
									}
								}
								//mCurrentDragAnimal->getLevel() kollar vilken som är snabbaste hastigheten
								if(level == j && mCurrentDragAnimal->getLevel() != level && mSpotVector[k]->getPrototypeAnimal() == 0 && mSpotVector[k]->getAfraidAnimal() == false){
									//aktiviera ljus
									mSpotVector[k]->setColorSpot(sf::Color(255,255,255,255));
									mSpotVector[k]->setOriginalColor(sf::Color(255,255,255,255));

								}else if(mCurrentDragAnimal->getLevel() == level && mSpotVector[k]->getPrototypeAnimal() == 0 && mSpotVector[k]->getAfraidAnimal() == false){
									//aktiviera ljus snabbt
									mSpotVector[k]->setColorSpot(sf::Color(0,255,0,255));
									mSpotVector[k]->setOriginalColor(sf::Color(0,255,0,255));
								}
							}
						}
					}
				}
			}
		}

		if(mCurrentDragAnimal != 0){
			float floatSpeed = 0.75;
			mGrabOffset.x *= floatSpeed;
			mGrabOffset.y *= floatSpeed;
			mCurrentDragAnimal -> setPos(mousePosition + mGrabOffset);
		}

}

float TaktikMeny::getDistance(const sf::Vector2f& v1, const sf::Vector2f& v2){
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	float distance = std::sqrt(dx*dx + dy*dy);
	return distance;
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
				std::vector<Spot*> intersectingSpots;
				for(SpotVector::size_type j = 0; j < mSpotVector.size(); j++){
					int level = mSpotVector[j]->getLevel();
					//om positionen på nummret i speedvectorn är detsamma som spottens position

					//crashar utan mCurrentDragAnimal != 0
					if(level == i && mCurrentDragAnimal != 0){
						//sparar alla spots djuret intersectar med /Robin
						
						if(mSpotVector[j]->getActSpot() == true && mSpotVector[j]->getPrototypeAnimal() == 0 && mCurrentDragAnimal->getSprite()->getGlobalBounds().intersects(mSpotVector[j]->getSprite()->getGlobalBounds())){
							
							intersectingSpots.push_back(mSpotVector[j]);

						}
					}	
				}
				// om den intersecar med nån spot /Robin
				if(!intersectingSpots.empty()){
					//kolla vilken som är närmast /Robin
					Spot* closestSpot = intersectingSpots[0];
					float closestDistance = 512;

					for(SpotVector::size_type k = 0; k  < intersectingSpots.size(); k++){
						sf::Vector2f v1 = mCurrentDragAnimal->getSprite()->getPosition();
						sf::Vector2f v2 = intersectingSpots[k]->getSprite()->getPosition();
						float distance = getDistance(v1,v2);

						if(distance < closestDistance){
							closestDistance = distance;
							closestSpot = intersectingSpots[k];
									
						}
					}
					//sätt djuret på den platsen /Robin
					closestSpot->setPrototypeAnimal(mCurrentDragAnimal);
					mCurrentDragAnimal->setPos(closestSpot->getSprite()->getPosition());
					mCurrentDragAnimal->setStandardSpeed(mSpeedVector[i]);

					mCurrentDragAnimal = 0;
				}
			}
		}
		if(mCurrentDragAnimal != 0){
			mCurrentDragAnimal->setPos(mCurrentDragAnimal->getStartPos());
		}
		
		mCurrentDragAnimal = 0;

		for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
			if((*i)->getPrototypeAnimal() == 0){
				(*i)->setAfraidAnimal(false);
				(*i)->setActSpot(false);
				(*i)->setColorSpot(sf::Color(255,255,255,255));
			}
		}

		for(SpotVector::size_type i = 0; i < mSpotVector.size(); i++){
			//kollar alla spots och ser om växtdjur har tomma platser bakom sig så ska inte de de står på vara rodjursplatsde
			if(mSpotVector[i]->getPrototypeAnimal() != 0 && i >= 1){
				if(mSpotVector[i]->getPrototypeAnimal()->getAnimalType() == "plant" && mSpotVector[i-1]->getPrototypeAnimal() == 0){

					//måste egentligen kolla igenom och sätta rätt färg här.
					mSpotVector[i]->resetColor();
					mSpotVector[i]->setAfraidAnimal(false);
				}
			}
		}

	}
}

void TaktikMeny::readFromFile(){

	std::vector<std::string> abilities = LevelManager::getInst().getAbilitiesOnLevel();

	tinyxml2::XMLDocument doca;
	doca.LoadFile("Resources/Data/Abilities.xml");

	float abilityNumber = 0;

	sf::Vector2f startPosition = sf::Vector2f(140,615);
	sf::Vector2f distance = sf::Vector2f(200,0);
	sf::Vector2f distance2 = sf::Vector2f(150,0);

	sf::Vector2f position = startPosition;

	for(std::vector<std::string>::iterator i = abilities.begin(); i != abilities.end();i++){
		tinyxml2::XMLElement *elm = doca.FirstChildElement("Abilities")->FirstChildElement((*i).c_str());

		std::string atexture = elm->FirstChildElement("Texture")->GetText();

		std::string itexture = elm->FirstChildElement("InfoPicture")->GetText();

		if(abilityNumber != 0){
			if((int)abilityNumber % 2 == 1){
				position += distance;
			}else{
				position += distance2;
			}
		}

		mAbilityButtons.push_back(new FakeAbilityButton(position,atexture,itexture));

		abilityNumber++;
	}

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
	
	mGui.setTexture(*ResourceManager::getInst().getTexture(doc.FirstChildElement("Gui")->GetText()));
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

