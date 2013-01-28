#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture texture, sf::Vector2f position, float speed) : mTexture(texture), mPosition(position), mSpeed(speed){

	mSprite.setTexture(mTexture);
}

Obstacle::~Obstacle(){

}

sf::Sprite* Obstacle::getSprite(){

	return mSprite;
}

void Obstacle::update(){

	mSprite.setPosition(mPosition);
	
}


void Obstacle::render(){

}
	

sf::FloatRect* Obstacle::getRect(){


}

bool Obstacle::getAlive(){

	return 0;
}

