#include "Animal.h"
#include "Animation.h"
#include <iostream>


Animal::Animal(Animation* animation, sf::Vector2f position, float speed) : 
	mAnimation(animation),
	currentAnimation(0), 
	mPosition(position),
	mSpeed(speed),
	mID("Animal")
{
	
}

Animal::~Animal(){

} 

void Animal::update(){

	mPosition.x += calculateSpeed(mSpeed);
	mAnimation->update();
	mAnimation->setPosition(mPosition);

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
	// clock
	//kolöllllla om dennna funkar  <------------------------------

	for(ModSet::iterator i = mModSet.begin(); i != mModSet.end(); i++){
		for(ModSet::iterator j = mModSet.begin(); j != mModSet.end(); j++){
			if((*i)->getID() != (*i)->getID()){
				if(entity->getID() == "Animal" && mPosition.x < entity->getPos().x){
					int time = 1;//<--------------------------------------ändra
					int speed = 0;//<--------------------------------------ändra
					mModSet.insert(new SpeedMod(time, speed, "AnimalMod"));
					std::cout<<"kollision mellan djur"<<std::endl;
				}
			}
		}
	}
}

sf::FloatRect* Animal::getRect(){
	return &mAnimation->getSprite()->getGlobalBounds();
}

bool Animal::getAlive(){
	return 0; // <--------------------------------------------OSÄKER OPÅ OM FUNKTIONEN BEHÖVSVSV
}

void Animal::setMod(SpeedMod* speedModv){
	// clock

	for(ModSet::iterator i = mModSet.begin(); i != mModSet.end(); i++){
		for(ModSet::iterator j = mModSet.begin(); j != mModSet.end(); j++){
			if((*i)->getID() != (*i)->getID()){
				mModSet.insert(speedModv);
			}
		}
	}
}

std::string Animal::getID(){
	return mID;
}

sf::Vector2f Animal::getPos(){
	return mPosition;
}