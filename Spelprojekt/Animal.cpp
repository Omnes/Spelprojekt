#include "Animal.h"
#include "Animation.h"


Animal::Animal(std::vector<Animation*> animation, sf::Vector2f position, float speed)
	: mAnimation(animation)
	, currentAnimation(0)
	, mPosition(position)
	, mSpeed(speed){
	
}

Animal::~Animal(){

}

void Animal::update(){

	mPosition.x += mSpeed;
	mAnimation->setPosition(mPosition);

}

sf::Sprite* Animal::getSprite(){
	return mAnimation->getSprite();
}
