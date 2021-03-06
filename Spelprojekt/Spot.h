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

	void update();

	void setTakenSpot(bool taken);
	bool getTakenSpot();

	void setColorSpot(sf::Color color);
	sf::Color getColorSpot();

	sf::Sprite* getSprite();

	void setPrototypeAnimal(AnimalPrototype* PlacedAnimal);
	AnimalPrototype* getPrototypeAnimal();

	void setAfraidAnimal(bool afraid);
	bool getAfraidAnimal();

	void setOriginalColor(sf::Color originalColor);
	void resetColor();

private:

	sf::Texture mTexture;
	sf::Sprite *mSprite;
	sf::IntRect mRect;
	AnimalPrototype* mPlacedAnimal;

	bool mActSpot;
	bool mTaken;
	
	sf::Color mColor;
	sf::Color mOriginalColor;

	int mLevel;

	bool mExtraSpeed; // kan �ndra till float sen
};

#endif