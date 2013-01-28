#include "Animal.h"
#include "Animation.h"


Animal::Animal(Animation* animation, sf::Vector2f position, float speed)
	: mAnimation(animation)
	, currentAnimation(0)
	, mPosition(position)
	, mSpeed(speed){
	
}

Animal::~Animal(){

} 

void Animal::update(){

	mPosition.x += calculateSpeed(mSpeed);
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
