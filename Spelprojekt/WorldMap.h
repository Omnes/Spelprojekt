#ifndef WORLDMAP
#define WORLDMAP
#include "States.h"

class WorldMap : public States{

public:

	WorldMap();
	~WorldMap();
	virtual void update();
	virtual void render();

};

#endif