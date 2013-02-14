#ifndef POPSTATETWICE
#define POPSTATETWICE

#include "Event.h"
#include "StateManager.h"

class PopStateTwice: public Event{
public:
	void update(){
		StateManager::getInst().popState();
		StateManager::getInst().popState();
	}
	PopStateTwice(){}
	~PopStateTwice(){}
};



#endif
