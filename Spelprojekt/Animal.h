#ifndef ANIMAL
#define ANIMAL

#include <vector>
#include <set>
#include <SFML\Graphics\Sprite.hpp>
#include "Entity.h"
#include <SFML\System\Clock.hpp>
#include <string>

class Animation;

class Animal : public Entity{

public:
	Animal(Animation* animation, sf::Vector2f position, float speed, std::string filePath);
	~Animal();
	void update();

	sf::FloatRect* getRect();
	sf::Sprite* getSprite();
	bool getAlive();
	void setAlive(bool alive);
	void collide(Entity* entity);
	
	std::string getID();
	sf::Vector2f getPos();
	std::string getFilePath();
	virtual float getCurrentSpeed();
	void setSpeedIncrease(float speedIncrease);
	
	float doDamage();

private:
	Animation* mAnimation;
	int currentAnimation;
	float mSpeed;
	float mCurrentSpeed;
	float mSpeedIncrease;
	float mCalcSpeed;
	sf::Vector2f mPosition;
	bool mAlive;
	int mCollideCooldown;

	std::string mFilePath;

	std::string mID;

	
};





#endif