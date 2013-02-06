#ifndef ADDTAKTIK
#define ADDTAKTIK
#include "Event.h"
#include "StateManager.h"
#include "Taktikmeny.h"

class AddTaktik : public Event{

public:

	AddTaktik(){}
	~AddTaktik(){}
	virtual void update(){StateManager::getInst().addState(new TaktikMeny);}

};

#endif 