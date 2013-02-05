#ifndef ADDPAUSE
#define ADDPAUSE
#include "Event.h"
#include "StateManager.h"

class AddPause : public Event{

public:

	AddPause(){}
	~AddPause(){}
	virtual void update(){StateManager::getInst().addState("pausemenu");}

};

#endif 