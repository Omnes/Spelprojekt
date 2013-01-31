#ifndef SPOT_H
#define SPOT_H

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Texture.hpp"
#include <iostream>

class ResourceManager;

class Spot{
public:
	Spot(int level, sf::Vector2f position);
	~Spot();
	
	void activateSpot(bool dragAnimal);
	int getLevel();
	sf::Sprite* getSprite();
	
private:

	sf::Texture mTexture;
	sf::Sprite *mSprite;
	sf::IntRect mRect;

	int mLevel;
};

#endif