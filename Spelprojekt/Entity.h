#ifndef ENTITY
#define ENTITY
#include <SFML\Graphics\Sprite.hpp>
#include "SpeedMod.h"

class Entity{
public:
	virtual ~Entity(){};
	virtual void update()=0;

	virtual sf::FloatRect* getRect()=0;
	virtual sf::Sprite* getSprite()=0;
	virtual bool getAlive()=0;
	virtual void collide(Entity* entity)=0;
	virtual void setMod(SpeedMod* speedMod)=0;

	//animation
	//etc...

};

#endif