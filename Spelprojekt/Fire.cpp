#include "Fire.h"
#include "ResourceManager.h"
#include <iostream>

Fire::Fire(sf::Vector2f position,float speed): mID("Fire"), mPosition(position), mSpeed(speed), mAlive(true),mFireSystem("Firewall",500),mSmokeSystem("Smoke",500){
	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Animals/eld.png"));
	mFireSystem.setBlendMode(sf::BlendAdd);
	mSmokeSystem.setBlendMode(sf::BlendAlpha);
	mSprite.setColor(sf::Color(0,0,0,0));
}

void Fire::update(){
	
	mPosition.x += mSpeed;
	mEmitter.setPosition(mPosition);
	mEmitter.burst(mFireSystem,sf::FloatRect(-100,0,150,720),17);
	mEmitter.burst(mSmokeSystem,sf::FloatRect(-150,0,100,720),3);
	mSprite.setPosition(mPosition);
}

sf::FloatRect* Fire::getRect(){
	return &mSprite.getGlobalBounds();
}

sf::Sprite* Fire::getSprite(){
	return &mSprite;
}

bool Fire::getAlive(){
	return mAlive;
}

void Fire::setAlive(bool alive){
	if (alive == false)
		std::cout << "du dödade just elden! är du säker ÅP att det var det du ville göra?" << std::endl;
	mAlive = alive;
}

void Fire::collide(Entity* entity){
	entity->setAlive(false);
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

float Fire::doDamage(){
	return 0.0;// gör inget
}