#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture* texture, sf::Vector2f position, float speed, std::string ID) : 
mTexture(texture), mPosition(position), mSpeed(speed), mID(ID), mAlive(true){

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

std::string Obstacle::getID(){
	return mID;
}

void Obstacle::collide(Entity* entity){
	int tid = 1;
	if(entity->getID() == "Animal"){
		entity->setMod(new SpeedMod(tid, 0, mID));
	}
}

void Obstacle::setMod(SpeedMod* speedMod){
	//denna ska inte göra något.
}

sf::Vector2f Obstacle::getPos(){
	return mPosition;
}