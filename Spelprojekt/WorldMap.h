#ifndef WORLDMAP
#define WORLDMAP
#include "States.h"
#include "LevelButton.h"
#include "FactButton.h"
#include "LevelManager.h"
#include "Button.h"
#include "ParticleManager.h"
#include "SFML\Graphics\Texture.hpp"
#include "tinyxml2.h"
#include <string> // kanske inte beh�vs (se: saveToFile(std::string))
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

	void setDeadAnimals(std::vector <std::string> deadAnimals);

	std::string getMusic();

	int getSection();
	bool getNewWorld();
	void doCutscene();



private:

	typedef std::vector <LevelButton*> ButtonVector;
	ButtonVector mButtonVector;

	typedef std::vector <std::vector<std::vector<std::string>>> WorldVector;
	WorldVector mWorldVector;

	typedef std::vector <std::string> BurnedLevelVector;
	BurnedLevelVector mBurnedLevelVector;

	typedef std::vector <std::string> DeadAnimalVector;
	DeadAnimalVector mDeadAnimalVector;

	std::vector<std::string> mCutscenes;

	std::string mMusic;

	sf::Sprite mSprite;

	int mWorld, mSub, mCurrentWorld, mSection, mCurrentSection;

	int mLevelCount;

	FactButton* mFactButton;

	//ta bort denna
	int mCount;

	bool mNewWorld;

	int mWorldMax, mSectionMax;

};

#endif