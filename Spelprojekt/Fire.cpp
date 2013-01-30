#include "Fire.h"
#include "ResourceManager.h"

Fire::Fire(sf::Vector2f position,float speed): mID("Fire"), mPosition(position), mSpeed(speed), mAlive(true){
	mSprite.setTexture(*ResourceManager::getInst().getTexture("eld.png"));
}

void Fire::update(){
	mPosition.x += mSpeed;
	mSprite.setPosition(mPosition);
}

sf::FloatRect* Fire::getRect(){
	return &mSprite.getGlobalBounds();
}

sf::Sprite* Fire::getSprite(){
	return &mSprite;
}

bool Fire::getAlive(){
	return true;
}

void Fire::collide(Entity* entity){
	
}

void Fire::setMod(SpeedMod* speedMod){
	delete speedMod;
}

std::string Fire::getID(){
	return mID;
}

sf::Vector2f Fire::getPos(){
	return mPosition;
}

Fire::~Fire(){

}