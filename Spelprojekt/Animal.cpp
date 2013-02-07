#include "Animal.h"
#include "Animation.h"
#include <iostream>


Animal::Animal(Animation* animation, sf::Vector2f position, float speed, std::string filePath) : 
	mAlive(true),
	mAnimation(animation),
	currentAnimation(0), 
	mPosition(position),
	mSpeed(speed),
	mID("Animal"),
	mFilePath(filePath){
	
}

Animal::~Animal(){
	delete mAnimation;
} 

void Animal::update(){

	mPosition.x += calculateSpeed(mSpeed);
	mAnimation->update();
	mAnimation->setPosition(mPosition);


	for(ModSet::iterator i = mModSet.begin(); i != mModSet.end();){
		if(!(*i)->getAlive()){
			i = mModSet.erase(i);

		}else{
			i++;
		}
	}
}

float Animal::calculateSpeed(float speed){

	for(std::set<SpeedMod*>::iterator i = mModSet.begin(); i != mModSet.end(); i++){
		speed *= (*i)->getMod();
	}

	return speed;
}

sf::Sprite* Animal::getSprite(){
	return mAnimation->getSprite();
}

void Animal::collide(Entity* entity){
	int time = 1;

	if(entity->getID() == "Animal" && mPosition.x < entity->getPos().x){
		int speed = 0;
		setMod(new SpeedMod(time, speed, "AnimalMod"));
	}

}

sf::FloatRect* Animal::getRect(){
	return &mAnimation->getSprite()->getGlobalBounds();
}

bool Animal::getAlive(){
	return mAlive; // <--------------------------------------------OSÄKER OPÅ OM FUNKTIONEN BEHÖVSVSV, jepp det gör den används redan flitigt
}

void Animal::setAlive(bool alive){
	mAlive = alive;
}

void Animal::setMod(SpeedMod* speedMod){
	// clock
	bool found = false;
	for(ModSet::iterator i = mModSet.begin(); i != mModSet.end(); i++){
		if((*i)->getID() == speedMod->getID()){
			found = true;
		}
	}

	if(!found){
		mModSet.insert(speedMod);
	}else{
		delete speedMod;
	}
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