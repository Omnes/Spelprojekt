#ifndef WORLDMAP
#define WORLDMAP
#include "States.h"
#include "LevelButton.h"

class WorldMap : public States{

public:

	WorldMap();
	~WorldMap();
	virtual void update();
	virtual void render();

private:

	std::vector<LevelButton*> mButtons;
};

#endif