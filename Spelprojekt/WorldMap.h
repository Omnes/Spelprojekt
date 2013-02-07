#ifndef WORLDMAP
#define WORLDMAP
#include "States.h"
#include "LevelButton.h"

#include "tinyxml2.h"

class WorldMap : public States{

public:

	WorldMap();
	~WorldMap();
	virtual void update();
	virtual void render();
	void readFromFile();

private:

	typedef std::vector <LevelButton*> ButtonVector;
	ButtonVector mButtonVector;

	typedef std::vector <std::string> PlayedLevels;
	PlayedLevels mPlayedLevels;

};

#endif