#include "Taktikmeny.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "LevelManager.h"
#include "Spot.h"

TaktikMeny::TaktikMeny() : 
	mCurrentDragAnimal(0),
	mLevelTop(0),
	mLevelMiddle(0),
	mLevelGround(0)
{
	//mFakeAnimals.push_back(new AnimalPrototype("GoliathSpider.xml"));//<--- ta bort?

	//mSpotVector = LevelManager::getInst().getSpotsOnLevel();// h�mta spotvector fr�n levelnmaanager
	receiveAnimals();
	placeSpots();
}

TaktikMeny::~TaktikMeny(){}


void TaktikMeny::update(){

	sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()));

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(mCurrentDragAnimal==0){
			for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); ++i){
				sf::FloatRect rect = (*i) -> getGlobalBounds();
				if(rect.contains(position)){
					mCurrentDragAnimal = (*i);
				}
			}

			if(mCurrentDragAnimal !=0){
				mSpeedVector = mCurrentDragAnimal->getSpeedVector();
				//g�r igenom animal speedvector som inneh�ller tre olika hastigheteter
				for(SpeedVector::size_type j = 0; j < mSpeedVector.size(); j++){
					//om speedvector inte har ngn nolla i sig
					if(mSpeedVector[j] != 0){
						//g�r igenom de olika spotsen
						for(SpotVector::iterator k = mSpotVector.begin(); k != mSpotVector.end(); k++){
							int level = (*k)->getLevel();
							//om positionen p� nummret i speedvectorn �r detsamma som spottens position
							if(level == j){
								//aktiviera ljus
								(*k)->activateSpot(true);
							}
						}
					//inte t�nd <-----------------------------------------
					}else{
						for(SpotVector::iterator k = mSpotVector.begin(); k != mSpotVector.end(); k++){
							int level = (*k)->getLevel();
							if(level == j){
								(*k)->activateSpot(false);
							}
						}
					}
				}
			}
		}
		if(mCurrentDragAnimal !=0){

			mCurrentDragAnimal -> setPos(position);
		}
	}else{
		//if �ver en plats osv..
		if(mCurrentDragAnimal !=0){
			//sluta lys <-------------------------------
			for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
				(*i)->activateSpot(false);
			}
			mCurrentDragAnimal = 0;
		}
	}

}

void TaktikMeny::render(){
	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}
	for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite()); 
	}

}


//tar emot och placerar ut animaler innan de kan placeras
void TaktikMeny::receiveAnimals(){
	sf::Vector2f startPos = sf::Vector2f(300,0);
	sf::Vector2f distance = sf::Vector2f(50,0);
	mFakeAnimals = LevelManager::getInst().getAnimalsOnLevel();
	for(FakeAnimals::size_type i = 0; i < mFakeAnimals.size(); i++){
		mFakeAnimals[i]->setPos(startPos + sf::Vector2f(distance.x*i,distance.y*i));
	}
}

void TaktikMeny::placeSpots(){
	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); i++){
		//h�mtar var alla olika prototypeanimals ska ligga. och l�gger de i en vektor
		//ska sedan kolla igenom vektorn och r�kna hur m�nga olika platser det �r p� varje.
		mLevelVector.push_back((*i)->getLevel());
	}

	//s�tter hur m�nga platser det finns per niv� ground/middle/top
	for(LevelVector::iterator i = mLevelVector.begin(); i != mLevelVector.end(); i++){
		if((*i) == 0){
			mLevelTop++;
		}else if((*i) == 1){
			mLevelMiddle++;
		}else{
			mLevelGround++;
		}
	}

	//flyttar ner spots fr�n toppen till ground
	mLevelGround += mLevelTop / 2;
	mLevelTop = ((float)mLevelTop / 2) + 0.5;

	mPosVector.push_back(mLevelTop);
	mPosVector.push_back(mLevelMiddle);
	mPosVector.push_back(mLevelGround); // v�rdel�st ???

	int temp = 30;
	int temp2 = 30; // fixa detta snyggare sen ??
	
	//placerar ut spots 
	for(int i = 0; i < 2; i++){
		temp *= (i + 1);
		for(int j = 0; j < mPosVector[i]; j++){
			temp2 *= (j + 1);
			mSpotVector.push_back(new Spot(i, sf::Vector2f(temp, temp2)));
		}
	}
}

States* TaktikMeny::createNew(){
	return new TaktikMeny;
}
