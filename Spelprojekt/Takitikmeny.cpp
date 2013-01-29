#include "Taktikmeny.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>

TaktikMeny::TaktikMeny(): mCurrentDragAnimal(0){
	mFakeAnimals.push_back(new AnimalPrototype("GoliathSpider"));
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
		mCurrentDragAnimal = 0;
	}

}

void TaktikMeny::render(){

}