#include "Obstacle.h"
#include <SFML\System\Clock.hpp>

Obstacle::Obstacle(sf::Texture* texture, sf::Vector2f position, float speed, std::string ID) : 
mTexture(texture), mPosition(position), mSpeedMod(speed), mID(ID), mAlive(true){

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
	int tid = 50;
	
	if(entity->getID() == "Animal"){

		if (!entity->checkMod(mID)){
			entity->setMod(new SpeedMod(tid, mSpeedMod, mID));
		}
	}
}

void Obstacle::setMod(SpeedMod* speedMod){
	//denna ska inte göra något.
}

sf::Vector2f Obstacle::getPos(){
	return mPosition;
}