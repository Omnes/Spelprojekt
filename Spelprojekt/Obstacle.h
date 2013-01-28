#ifndef OBSTACLE
#define OBSTACLE
#include "Entity.h"
#include <SFML\Graphics\Texture.hpp>

class Obstacle : public Entity{

public:

	Obstacle(sf::Texture texture, sf::Vector2f position, float speed);
	~Obstacle();
	virtual void update();
	virtual sf::Sprite* getSprite();
	virtual void render();
	virtual sf::FloatRect* getRect();
	virtual bool getAlive();


private:

	sf::Texture mTexture;
	sf::Vector2f mPosition;
	float mSpeed;
	sf::Sprite mSprite;
	SpeedMod *mSpeedmod;
};

#endif