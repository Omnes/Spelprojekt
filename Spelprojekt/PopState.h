#ifndef POPSTATE
#define POPSTATE

#include "Event.h"
#include "StateManager.h"

class PopState: public Event{
public:
	void update(){StateManager::getInst().popState();}
	PopState(){}
	~PopState(){}
};



#endif