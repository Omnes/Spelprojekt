#ifndef ANIMAL
#define ANIMAL

#include <vector>
#include <set>
#include <SFML\Graphics\Sprite.hpp>
#include "SpeedMod.h"
#include "Entity.h"
#include <SFML\System\Clock.hpp>

class Animation;

class Animal : public Entity{

public:
	Animal(Animation* animation, sf::Vector2f position, float speed);
	~Animal();
	void update();

	sf::FloatRect* getRect();
	sf::Sprite* getSprite();
	bool getAlive(); // <----------------------------kanske ta bort denna funktion !??!
	void setAlive(bool alive);
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
	bool mAlive;
	sf::Clock collideCooldown;

	std::string mID;

	float calculateSpeed(float speed);
};





#endif