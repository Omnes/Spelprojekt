#ifndef SPOT
#define SPOT

#include <SFML\Graphics\Sprite.hpp>

class ResourceManager;

class Spot{
public:
	Spot(int level);
	~Spot();
	
	void activateSpot(bool dragAnimal);
	int getLevel();
	sf::Sprite* getSprite();
	


private:
	sf::Texture* mTexture;
	sf::Sprite* mSprite;
	sf::IntRect mRect;

	int mLevel;
};

#endif