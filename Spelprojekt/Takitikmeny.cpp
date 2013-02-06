#include "Taktikmeny.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "LevelManager.h"
#include "Spot.h"
#include "AnimalPrototype.h"

#include <SFML\Graphics\RectangleShape.hpp>

TaktikMeny::TaktikMeny() : 
	mCurrentDragAnimal(0),
	mLevelTop(0),
	mLevelMiddle(0),
	mLevelGround(0)
{

	receiveAnimals();
	placeSpots();
}

TaktikMeny::~TaktikMeny(){}


void TaktikMeny::update(){

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		isClicked();
	}else{
		isNotClicked();
	}
}

void TaktikMeny::render(){

	for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}

	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}

}


//tar emot och placerar ut animaler innan de kan placeras
void TaktikMeny::receiveAnimals(){
	sf::Vector2f startPos = sf::Vector2f(500,300);
	sf::Vector2f distance = sf::Vector2f(128,0);
	mFakeAnimals = LevelManager::getInst().getAnimalsOnLevel();
	for(FakeAnimals::size_type i = 0; i < mFakeAnimals.size(); i++){
		mFakeAnimals[i]->setPos(startPos + sf::Vector2f(distance.x*i,distance.y*i));
		mFakeAnimals[i]->setStartPos(startPos + sf::Vector2f(distance.x*i,distance.y*i));
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

	int xDistance = 250;
	int yDistance = 200;
	
	int startX = 80;

	//placerar ut spots 
	for(int i = 0; i < 3/* == antal level på en bana*/; i++){
		for(int j = 0; j < mPosVector[i]; j++){
			mSpotVector.push_back(new Spot(i, sf::Vector2f(startX + j*xDistance, i*yDistance)));
		}
	}
}


void TaktikMeny::createAnimals(){

	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); ++i){
		mAnimalVector.push_back((Entity*)(*i)->createAnimal());
	}

	LevelManager::getInst().setAnimalPosition(mAnimalVector);
}

void TaktikMeny::isClicked(){
	sf::Vector2f musPosition = sf::Vector2f(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()));

		if(mCurrentDragAnimal == 0){

			for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); ++i){
				if((*i)->getSprite()->getGlobalBounds().contains(musPosition)){
					mCurrentDragAnimal = (*i);
					mGrabOffset = mCurrentDragAnimal->getPos() - musPosition;
				}
			}


			//kan fucka ur om man tar djur utanför spotboxen
			for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
				if((*i)->getSprite()->getGlobalBounds().contains(musPosition)){
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
							if(level == j){
								//aktiviera ljus
								(*k)->setActSpot(true);
								(*k)->setColorSpot(true);
							}
						}
					}
				}
			}

		}

		if(mCurrentDragAnimal !=0){
			mCurrentDragAnimal -> setPos(musPosition + mGrabOffset);
		}

}

void TaktikMeny::isNotClicked(){

	//om mCurrentAnimal är över en spot
	if(mCurrentDragAnimal != 0){

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
							mCurrentDragAnimal = 0;
							(*j)->setTakenSpot(true);
							(*j)->setColorSpot(true);

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
				(*i)->setActSpot(false);
				(*i)->setColorSpot(false);
			}
		}

	}

}