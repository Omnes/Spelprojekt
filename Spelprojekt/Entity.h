#ifndef ENTITY
#define ENTITY

#include <SFML\Graphics\Sprite.hpp>

class Entity{
public:
	virtual ~Entity(){};
	virtual void update()=0;
<<<<<<< HEAD
=======
	//virtual void render()=0;

>>>>>>> sean
	virtual sf::FloatRect* getRect()=0;
	virtual sf::Sprite* getSprite()=0;
	virtual bool getAlive()=0;
	virtual void collide(Entity* entity)=0;

	//animation
	//etc...

};

#endif