#ifndef ADDOPTION
#define ADDOPTION
#include "Event.h"
#include "StateManager.h"

class AddOptions : public Event{

public:

	AddOptions(){}
	~AddOptions(){}
	virtual void update(){StateManager::getInst().addState("optionsmenu");}

};

#endif 