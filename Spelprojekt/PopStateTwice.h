#ifndef POPSTATETWICE
#define POPSTATETWICE

#include "Event.h"
#include "StateManager.h"

class PopTwiceState: public Event{
public:
	void update(){StateManager::getInst().popState();}
	PopState(){}
	~PopState(){}
};



#endif