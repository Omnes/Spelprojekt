#include "Obstacle.h"
#include <SFML\System\Clock.hpp>

Obstacle::Obstacle(Animation* animation, sf::Vector2f position, float speed, std::string ID) : 
	mAnimation(animation),
	mPosition(position),
	mSpeedEffect(speed),
	mID(ID),
	mAlive(true)
{
	mAnimation->setPosition(mPosition);

}

Obstacle::~Obstacle(){
	delete mAnimation;
}

sf::Sprite* Obstacle::getSprite(){

	return mAnimation->getSprite();
}

void Obstacle::update(){

	mAnimation->update();
	//mAnimation->setPosition(mPosition);
}
	

sf::FloatRect* Obstacle::getRect(){

	return 0;//&mSprite.getGlobalBounds();
}

bool Obstacle::getAlive(){

	return mAlive;
}

void Obstacle::setAlive(bool alive){
	mAlive = alive;
}

std::string Obstacle::getID(){
	return mID;
}

void Obstacle::collide(Entity* entity){

}


sf::Vector2f Obstacle::getPos(){
	return mPosition;
}

float Obstacle::doDamage(){
	return mSpeedEffect;
}