#ifndef WORLDMAP
#define WORLDMAP
#include "States.h"
#include "LevelButton.h"
#include "LevelManager.h"

#include "SFML\Graphics\Texture.hpp"
#include "tinyxml2.h"
#include <string> // kanske inte behövs (se: saveToFile(std::string))
#include <vector>

class WorldMap : public States{

public:

	WorldMap();
	~WorldMap();
	virtual void update();
	virtual void render();
	void readSave();
	void saveToFile(std::string currentLevel);

	void readButtons();

	void readWorld();
	void updateWorld();
	void setCurrentWorldOrSub(std::string currentLevel);

	void readAnimals();
	void readNewAnimals();



	std::string getMusic();


private:

	typedef std::vector <LevelButton*> ButtonVector;
	ButtonVector mButtonVector;

	typedef std::vector <std::vector<std::vector<std::string>>> WorldVector;
	WorldVector mWorldVector;

	typedef std::vector <std::string> BurnedLevelVector;
	BurnedLevelVector mBurnedLevelVector;

	typedef std::vector <std::string> FakeAnimals;
	FakeAnimals mFakeAnimals;

	std::string mMusic;

	sf::Sprite mSprite;

	int mWorld, mSub, mCurrentWorld, mSection, mCurrentSection;

	int mLevelCount;

};

#endif