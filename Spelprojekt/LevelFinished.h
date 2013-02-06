#ifndef LEVELFINISHED
#define LEVELFINISHED
#include "States.h"

class LevelFinished : public States{

public:
	LevelFinished();
	~LevelFinished();
	virtual void update();
	virtual void render();
};

#endif