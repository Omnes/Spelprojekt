#ifndef ENTITY
#define ENTITY

#include <SFML\Graphics\Sprite.hpp>

class Entity{
public:
	virtual void update();
	virtual void render();
	virtual sf::FloatRect getRect();
	virtual sf::Sprite getSprite();
	virtual bool getAlive();

	//animation
	//etc...

};

#endif