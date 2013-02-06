#ifndef ADDOPTION
#define ADDOPTION
#include "Event.h"
#include "StateManager.h"
#include "OptionsMeny.h"

class AddOptions : public Event{

public:

	AddOptions(){}
	~AddOptions(){}
	virtual void update(){StateManager::getInst().addState(new OptionsMeny);}

};

#endif 