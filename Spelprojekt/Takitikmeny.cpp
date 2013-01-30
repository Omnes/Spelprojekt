#include "Taktikmeny.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "LevelManager.h"
#include "Spot.h"

TaktikMeny::TaktikMeny(): mCurrentDragAnimal(0){
	mFakeAnimals.push_back(new AnimalPrototype("GoliathSpider.xml"));//<--- ta bort?

	//mSpotVector = LevelManager::getInst().getSpotsOnLevel();// h�mta spotvector fr�n levelnmaanager

	//receiveAnimals();
}

TaktikMeny::~TaktikMeny(){}


void TaktikMeny::update(){

	sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()));

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(mCurrentDragAnimal==0){
			for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); ++i){
				sf::FloatRect rect = (*i) -> getGlobalBounds();
				if(rect.contains(position)){
					//t�nd ljus <-----------------------------------------
					mCurrentDragAnimal = (*i);
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
			mCurrentDragAnimal = 0;
		}
	}

	
}

void TaktikMeny::render(){
	for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}
	//for(SpotVector::iterator i = mSpotVector.begin(); i != mSpotVector.end(); i++){
	//	WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	//}

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
		//h�mtar var alla olika prototypeanimals ska ligga. och l�gger de i en vektor
		//ska sedan kolla igenom vektorn och r�kna hur m�nga olika platser det �r p� varje.
		mAllLevelVector.push_back((*i)->getLevel());
	}
<<<<<<< HEAD
	for(AllLevelVector::iterator i = mAllLevelVector.begin(); i != mAllLevelVector.end(); i++){
		if((*i) == 0){
			mLevelTop++;
		}else if((*i) == 1){
			mLevelMiddle++;
		}else{
			mLevelGround++;
		}

		mLevelGround += mLevelTop / 2; //robin hj�lp fixa denna funkation <------------
		mLevelTop = mLevelTop / 2;

	}

=======
}

States* TaktikMeny::createNew(){
	return new TaktikMeny;
>>>>>>> robin
}