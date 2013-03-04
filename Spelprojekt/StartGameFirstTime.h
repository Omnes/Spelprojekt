#ifndef STARTGAMEFIRSTTIME
#define STARTGAMEFIRSTTIME
#include "Event.h"
#include "StateManager.h"
#include "Tutorial.h"
#include "WorldMap.h"

class StartGameFirstTime : public Event{

public:

	StartGameFirstTime(){}
	~StartGameFirstTime(){}
	virtual void update(){StateManager::getInst().addState(new WorldMap); StateManager::getInst().addState(new Tutorial);}

};

#endif 
