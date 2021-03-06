#ifndef ANIMALPROTOTYPE
#define ANIMALPROTOTYPE

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include "tinyxml2.h"
#include <string>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Audio\Sound.hpp>
#include <vector>

class Animal;
class ResourceManager;
class Animation;
class SoundManager;

class AnimalPrototype{
public:
	AnimalPrototype(std::string filePath);
	~AnimalPrototype();
	
	void loadAnimal(std::string filePath);
	Animal* createAnimal(/*float bonusSpeed*/); 
	void setPos(sf::Vector2f position);
	void setStartPos(sf::Vector2f startPos);

	sf::Vector2f getStartPos();
	void setStandardSpeed(float stdSpeed);

	sf::Vector2f getPos();
	sf::FloatRect getGlobalBounds(); //<--------------ta bort denna
	sf::Sprite* getSprite();
	int getLevel();
	std::vector <float> getSpeedVector();

	void playSound();

	//int getCurrentLevel();
	//void setCurrentLevel(int currentLevel);

	std::string getAnimalType();

	void setExtraSpeed(float extraSpeed);


private:

	//float mTreeSpeed, mMiddleSpeed, mGroundSpeed;
	
	typedef std::vector <float> SpeedVector;
	SpeedVector mSpeedVector;
	std::string mFilePath;

	int mHighSpeed;
	float mAnimalHighSpeed;
	//farten den f�r
	float mStandardSpeed;

	sf::Vector2f mPosition;
	sf::Texture* mTex;
	sf::Sprite mSprite;
	std::string mAnimalType;
	//std::string mSound;

	sf::Sound mSound;

	float mFrameTick, mFrames;

	sf::Vector2f mStartPos;

	Animation* mAnimation;

	float mExtraSpeed;

};

#endif