#ifndef ADDTAKTIK
#define ADDTAKTIK
#include "Event.h"
#include "StateManager.h"

class AddTaktik : public Event{

public:

	AddTaktik(){}
	~AddTaktik(){}
	virtual void update(){StateManager::getInst().addState("taktikmenu");}

};

#endif 