#ifndef SPOT_H
#define SPOT_H

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Texture.hpp"
#include <iostream>
#include "AnimalPrototype.h"

class AnimalPrototype;

class Spot{
public:
	Spot(int level, sf::Vector2f position);
	~Spot();
	
	void setActSpot(bool dragAnimal);
	bool getActSpot();

	int getLevel();

	void setTakenSpot(bool taken);
	bool getTakenSpot();

	void setColorSpot(bool taken);

	sf::Sprite* getSprite();
	
private:

	sf::Texture mTexture;
	sf::Sprite *mSprite;
	sf::IntRect mRect;
	AnimalPrototype* mPlacedAnimal;

	bool mActSpot;
	bool mTaken;
	

	int mLevel;
};

#endif