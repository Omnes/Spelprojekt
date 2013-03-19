#include "Fire.h"
#include "ResourceManager.h"
#include <iostream>
#include "Animation.h"
#include "LevelManager.h"
#include "ActiveLayer.h"
#include "SoundManager.h"

Fire::Fire(sf::Vector2f position,float closeupspeed = 180)
	: mID("Fire")
	, mPosition(position)
	, mCloseupSpeed(closeupspeed)
	, mSpeed(0)
	, mAlive(true)
	, mFireSystem("Firewall",500)
	, mSmokeSystem("Smoke",770)
	, mPoofSystem("Smoke",50)
	, mDeathSound(*ResourceManager::getInst().getSoundBuffer("Resources/Sound/Effekts/Death_effekt.wav")){

	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Animals/eld.png"));
	mFireSystem.setBlendMode(sf::BlendAdd);
	mSmokeSystem.setBlendMode(sf::BlendAlpha);
	mSprite.setColor(sf::Color(0,0,0,0));
	mEmitter.setPosition(mPosition);
	mSprite.setPosition(mPosition);

}

void Fire::update(){
	//mSpeed += mAcceleration;
	mPosition.x += mSpeed;
	mEmitter.setPosition(mPosition);
	mEmitter.burst(mFireSystem,sf::FloatRect(-100,0,225,720),17);
	mEmitter.burst(mSmokeSystem,sf::FloatRect(-1000,0,950,720),10);
	mSprite.setPosition(mPosition-sf::Vector2f(50,0));

	if(mSpeedUpdateCooldown.getElapsedTime().asSeconds() > 0.5){
		std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
		float distance = 1000;
		for(std::vector<Entity*>::iterator i = entityVector->begin();i != entityVector->end();i++){
			if((*i)->getID() == "Animal"){
				int dist = (*i)->getPos().x - mPosition.x;
				if(dist < distance){
					distance = dist;
				}
			}
		}
		if(distance < 10 ){
			distance = 10;
		}

		mSpeed = distance/mCloseupSpeed;
		mSpeedUpdateCooldown.restart();
	}
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
	//mEmitter.setPosition(entity->getPos());
	//mEmitter.burst(mPoofSystem,30,10);
	Animation* animation = new Animation(ResourceManager::getInst().getTexture("Resources/Animals/death.png"),100,10,1);
	animation->setPosition(entity->getPos());
	LevelManager::getInst().getActiveLayer()->addAnimationEffekt(animation);
	entity->setAlive(false);
	SoundManager::getInst().play(mDeathSound);
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