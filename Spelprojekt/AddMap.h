#ifndef ADDMAP
#define ADDMAP
#include "Event.h"
#include "StateManager.h"
#include "WorldMap.h"

class AddMap : public Event{

public:

	AddMap(){}
	~AddMap(){}
	virtual void update(){StateManager::getInst().addState(new WorldMap);}

};

#endif 