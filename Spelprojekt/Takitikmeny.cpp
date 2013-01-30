#include "Taktikmeny.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "LevelManager.h"

TaktikMeny::TaktikMeny(): mCurrentDragAnimal(0){
	mFakeAnimals.push_back(new AnimalPrototype("GoliathSpider.xml"));//<--- ta bort?

	//mSpotVector = LevelManager::getInst().// hämta spotvector från levelnmaanager

	receiveAnimals();
}

TaktikMeny::~TaktikMeny(){}


void TaktikMeny::update(){

	sf::Vector2f position = sf::Vector2f(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()));

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(mCurrentDragAnimal==0){
			for(FakeAnimals::iterator i = mFakeAnimals.begin(); i != mFakeAnimals.end(); ++i){
				if((*i) -> getGlobalBounds().contains(position)){
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