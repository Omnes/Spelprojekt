#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture texture, sf::Vector2f position, float speed) : mTexture(texture), mPosition(position), mSpeed(speed){

	mSprite.setTexture(mTexture);
	
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

	return 0;

}

bool Obstacle::getAlive(){

	return 0;
}

