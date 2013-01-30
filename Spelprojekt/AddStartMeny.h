#ifndef ADDSTART
#define ADDSTART
#include "Event.h"
#include "StateManager.h"

class AddStartMeny : public Event{

public:

	AddStartMeny(){}
	~AddStartMeny(){}
	virtual void update(){StateManager::getInst().addState("startmenu");}

};

#endif 