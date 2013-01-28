#ifndef ANIMAL
#define ANIMAL

#include <vector>
#include <set>
#include <SFML\Graphics\Sprite.hpp>
#include "SpeedMod.h"
#include "Entity.h"

class Animation;

class Animal : public Entity{

public:
	Animal(Animation* animation, sf::Vector2f position, float speed);
	~Animal();
	void update();
	void render();

	sf::FloatRect* getRect();
	sf::Sprite* getSprite();
	bool getAlive(); // <----------------------------kanske ta bort denna funktion !??!
	void collide(Entity* entity);


private:
	Animation* mAnimation;
	int currentAnimation;
	float mSpeed;
	sf::Vector2f mPosition;
	std::set<SpeedMod*> mModSet;

	float calculateSpeed(float speed);
};





#endif