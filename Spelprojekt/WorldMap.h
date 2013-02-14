#ifndef WORLDMAP
#define WORLDMAP
#include "States.h"
#include "LevelButton.h"

#include "tinyxml2.h"
#include <string> // kanske inte beh�vs (se: saveToFile(std::string))

class WorldMap : public States{

public:

	WorldMap();
	~WorldMap();
	virtual void update();
	virtual void render();
	void readFromFile();
	void saveToFile(std::string levelName);

private:

	typedef std::vector <LevelButton*> ButtonVector;
	ButtonVector mButtonVector;

	typedef std::vector <std::string> PlayedLevels;
	PlayedLevels mPlayedLevels;

};

#endif