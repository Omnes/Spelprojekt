#ifndef ADDGAMEPLAY
#define ADDGAMEPLAY
#include "Event.h"
#include "StateManager.h"
#include "Gameplay.h"
class AddGameplay : public Event{

public:

	AddGameplay(){}
	~AddGameplay(){}
	virtual void update(){StateManager::getInst().addState(new Gameplay);}

};

#endif 