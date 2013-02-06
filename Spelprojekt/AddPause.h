#ifndef ADDPAUSE
#define ADDPAUSE
#include "Event.h"
#include "StateManager.h"
#include "PauseMeny.h"

class AddPause : public Event{

public:

	AddPause(){}
	~AddPause(){}
	virtual void update(){StateManager::getInst().addState(new PauseMeny);}

};

#endif 