#ifndef ANIMALPROTOTYPE
#define ANIMALPROTOTYPE

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include "tinyxml2.h"
#include <string>

class Animal;
class ResourceManager;
class Animation;

class AnimalPrototype{
public:
	AnimalPrototype();
	~AnimalPrototype();
	
	void loadAnimal();
	Animal* createAnimal(); // position, 
	void setPos(sf::Vector2f position);
	sf::Vector2f getPos();


private:

	float mTreeSpeed, mMiddleSpeed, mGroundSpeed;
	sf::Texture* mTex;
	std::string mAnimalType;
	float mFrameTick, mFrames;

	Animation* mAnimation;

};

#endif