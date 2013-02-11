#include "Obstacle.h"
#include <SFML\System\Clock.hpp>

Obstacle::Obstacle(sf::Texture* texture, sf::Vector2f position, float speed, std::string ID) : 
	mTexture(texture),
	mPosition(position),
	mSpeedEffect(speed),
	mID(ID),
	mAlive(true)
{

	mSprite.setTexture(*mTexture);

}

Obstacle::~Obstacle(){

}

sf::Sprite* Obstacle::getSprite(){

	return &mSprite;
}

void Obstacle::update(){

	mSprite.setPosition(mPosition);
}
	

sf::FloatRect* Obstacle::getRect(){

	return &mSprite.getGlobalBounds();
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