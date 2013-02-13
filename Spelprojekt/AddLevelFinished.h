#ifndef ADDLEVELFINISHED
#define ADDLEVELFINISHED
#include "Event.h"
#include "StateManager.h"
#include "LevelFinished.h"

class AddLevelFinished : public Event{

public:
	AddLevelFinished(){}
	~AddLevelFinished(){}
	virtual void update(){ 
		StateManager::getInst().popState();
		StateManager::getInst().addState(new LevelFinished);
	}

};


#endif