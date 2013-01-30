#ifndef ANIMALPROTOTYPE
#define ANIMALPROTOTYPE

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include "tinyxml2.h"
#include <string>
#include <SFML\Graphics\Sprite.hpp>

class Animal;
class ResourceManager;
class Animation;

class AnimalPrototype{
public:
	AnimalPrototype(std::string filePath);
	~AnimalPrototype();
	
	void loadAnimal(std::string filePath);
	Animal* createAnimal(); // position, 
	void setPos(sf::Vector2f position);
	sf::Vector2f getPos();
	sf::FloatRect& getGlobalBounds(); //<--------------ta bort denna
	sf::Sprite* getSprite();


private:

	float mTreeSpeed, mMiddleSpeed, mGroundSpeed;
	sf::Vector2f mPosition;
	sf::Texture* mTex;
	sf::Sprite mSprite;
	std::string mAnimalType;
	float mFrameTick, mFrames;

	Animation* mAnimation;

};

#endif