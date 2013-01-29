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
	int tid = 1;//<--------------------------------------ändra
	if(entity->getID() == "Animal"){
		entity->setMod(new SpeedMod(200, 0, mID));
	}
}

//gör ingenting
void Obstacle::setMod(SpeedMod* speedMod){
	//fel
}

sf::Vector2f Obstacle::getPos(){
	return mPosition;
}