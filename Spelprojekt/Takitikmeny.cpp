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
	mFakeAnimals.push_back(new AnimalPrototype("GoliathSpider.xml"));//<--- ta bort?

	//mSpotVector = LevelManager::getInst().getSpotsOnLevel();// hämta spotvector från levelnmaanager

	//receiveAnimals();
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
					//tänd ljus <-----------------------------------------
					mCurrentDragAnimal = (*i);
				}
			}
		}
		if(mCurrentDragAnimal !=0){
			mCurrentDragAnimal -> setPos(position);
		}
	}else{
		//if över en plats osv..
		if(mCurrentDragAnimal !=0){
			//sluta lys <-------------------------------
			mCurrentDragAnimal = 0;
		}
	}

}

void TaktikMeny::render(){
	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}
	for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
//		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite()); <-------------AVKOMMENTERA
	}

}


//tar emot och placerar ut animaler innan de kan placeras
void TaktikMeny::receiveAnimals(){
	//mFakeAnimals = LevelManager::getInst().getAnimalsOnLevel();
	//for(FakeAnimals::size_type i = 0; i < mFakeAnimals.size(); i++){
	//	//<---------------------------------det finns ingen startposition !!!!!!!!!!
	//	mFakeAnimals[i]->setPos(sf::Vector2f(mFakeAnimals[i-1]->getPos().x + 30, mFakeAnimals[i-1]->getPos().y));
	//}
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
	//mLevelTop = (mLevelTop / 2) + 0.5; <----------------------------fixa denna

	mPosVector.push_back(mLevelTop);
	mPosVector.push_back(mLevelMiddle);
	mPosVector.push_back(mLevelGround); // värdelöst ???

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