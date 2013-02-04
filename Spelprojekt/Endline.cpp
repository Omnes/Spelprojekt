#include "Endline.h"


Endline::Endline(sf::Vector2f position, sf::Texture *texture) : mTexture(texture), mID("Endline"){

	mSprite->setTexture(*mTexture);
	mSprite->setPosition(position);
}

Endline::~Endline(){
}

void Endline::update(){

}

sf::FloatRect* Endline::getRect(){

	return &mSprite->getGlobalBounds();
}

sf::Sprite* Endline::getSprite(){

	return mSprite;
}

bool Endline::getAlive(){
	return true;
}

void Endline::setAlive(bool alive){

}
	
void Endline::collide(Entity* entity){


}

void Endline::setMod(SpeedMod* speedMod){

}

std::string Endline::getID(){

	return mID;
}

sf::Vector2f Endline::getPos(){

	return mSprite->getPosition();
}