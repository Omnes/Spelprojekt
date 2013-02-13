#include "Animal.h"
#include "Animation.h"
#include <iostream>


Animal::Animal(Animation* animation, sf::Vector2f position, float speed, std::string filePath) : 
	mAlive(true),
	mAnimation(animation),
	currentAnimation(0), 
	mPosition(position),
	mSpeed(speed),
	mCalcSpeed(speed),
	mID("Animal"),
	mFilePath(filePath){

	
}

Animal::~Animal(){
	delete mAnimation;
} 

void Animal::update(){

	mAnimation->setCurrentAnimation(currentAnimation);
	currentAnimation = 0;

	mCurrentSpeed = mSpeed * mCalcSpeed;

	mPosition.x += mCurrentSpeed;

	mAnimation->update();
	mAnimation->setPosition(mPosition);

	//mCalcSpeed = mSpeed; //det här borde vi fixa på ngt random sätt. vet ej hur
	mCalcSpeed = 1;
}

sf::Sprite* Animal::getSprite(){
	return mAnimation->getSprite();
}

void Animal::collide(Entity* entity){
	int time = 50;
	float aCol = 1;
	float oCol = 1;

	

	if(entity->getID() == "Animal" && mPosition.x < entity->getPos().x){
		if(entity->getCurrentSpeed() == 0){
			currentAnimation = 1;
		}
		aCol = 0;
	}

	//sktriv om id som id
	//if(entity->getID() == "Stone" /*|| entity->getID() == "Gren"*/){
	//	currentAnimation = 1;
	//	oCol = entity->doDamage();
	//}else if(/*entity->getID() == "Sten" ||*/ entity->getID() == "Gren"){
	//	oCol = entity->doDamage();
	//}

	if(entity->getID() != "Animal"  && entity->getID() != "Fire"){
		if(entity->doDamage() == 0){
			currentAnimation = 1;
		}
		oCol = entity->doDamage();
	}


	mCalcSpeed = mCalcSpeed * aCol * oCol;

}

sf::FloatRect* Animal::getRect(){
	return &mAnimation->getSprite()->getGlobalBounds();
}

bool Animal::getAlive(){
	return mAlive; 
}

void Animal::setAlive(bool alive){
	mAlive = alive;
}

std::string Animal::getID(){
	return mID;
}

sf::Vector2f Animal::getPos(){
	return mPosition;
}

std::string Animal::getFilePath(){
	return mFilePath;
}

float Animal::doDamage(){
	return 0.0; //gör inget
};

float Animal::getCurrentSpeed(){
	return mCurrentSpeed;
}
