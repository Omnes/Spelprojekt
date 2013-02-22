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

	void setColorSpot(int taken);
	int getColorSpot();

	sf::Sprite* getSprite();

	void setPrototypeAnimal(AnimalPrototype* PlacedAnimal);
	AnimalPrototype* getPrototypeAnimal();

	void setAfraidAnimal(bool extraSpeed);
	bool getAfraidAnimal();

private:

	sf::Texture mTexture;
	sf::Sprite *mSprite;
	sf::IntRect mRect;
	AnimalPrototype* mPlacedAnimal;

	bool mActSpot;
	bool mTaken;
	
	int mColor;

	int mLevel;

	bool mExtraSpeed; // kan ändra till float sen
};

#endif