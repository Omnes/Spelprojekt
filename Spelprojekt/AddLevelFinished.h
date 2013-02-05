#ifndef ADDLEVELFINISHED
#define ADDLEVELFINISHED
#include "Event.h"
#include "StateManager.h"

class AddLevelFinished : public Event{

public:
	AddLevelFinished(){}
	~AddLevelFinished(){}
	virtual void update(){ StateManager::getInst().addState("levelfinished");}

};


#endif