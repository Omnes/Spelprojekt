#ifndef WORLDMAP
#define WORLDMAP
#include "States.h"
#include "LevelButton.h"

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
	void saveToFile();

	void readButtons();

	void readWorld();
	void updateWorld();
	void setCurrentWorldOrSub(std::string currentLevel);



	std::string getMusic();


private:

	typedef std::vector <LevelButton*> ButtonVector;
	ButtonVector mButtonVector;

	typedef std::vector <std::vector<std::vector<std::string>>> WorldVector;
	WorldVector mWorldVector;

	std::string mMusic;

	sf::Sprite mSprite;

	int mWorld, mSub;

	int mLevelCount;

};

#endif