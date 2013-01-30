#ifndef ADDGAMEPLAY
#define ADDGAMEPLAY
#include "Event.h"
#include "StateManager.h"

class AddGameplay : public Event{

public:

	AddGameplay(){}
	~AddGameplay(){}
	virtual void update(){StateManager::getInst().addState("gameplay");}

};

#endif 