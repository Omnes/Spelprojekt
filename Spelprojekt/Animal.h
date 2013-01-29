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
	//void render();

	sf::FloatRect* getRect();
	sf::Sprite* getSprite();
	bool getAlive(); // <----------------------------kanske ta bort denna funktion !??!
	void collide(Entity* entity);
	void setMod(SpeedMod* speedMod);
	std::string getID();
	sf::Vector2f getPos();

private:
	Animation* mAnimation;
	int currentAnimation;
	float mSpeed;
	sf::Vector2f mPosition;
	typedef std::set<SpeedMod*> ModSet;
	ModSet mModSet;

	std::string mID;

	float calculateSpeed(float speed);
};





#endif