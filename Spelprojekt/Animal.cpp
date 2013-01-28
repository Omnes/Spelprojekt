#include "Animal.h"
#include "Animation.h"


Animal::Animal(Animation* animation, sf::Vector2f position, float speed) : 
	mAnimation(animation),
	currentAnimation(0), 
	mPosition(position),
	mSpeed(speed),
	mID("Animal")
{
	
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

void Animal::collide(Entity* entity){
	//if(entity->getID() == "Animal" /*&& mPos < entity->getPos().x*/){
	//	//nersaktad !
	//}
}

//void Animal::render(){}

sf::FloatRect* Animal::getRect(){
	return &mSprite->getGlobalBounds();  // <--------------------------------------------nullptr. denna ska vara en floatrect
}

bool Animal::getAlive(){
	return 0; // <--------------------------------------------variabel som returnerar true eller false beroende på om gubben är vid liv. detta kan sättas i collide annars ? ?
}

void Animal::setMod(SpeedMod* speedModv ){}

std::string Animal::getID(){
	return mID;
}