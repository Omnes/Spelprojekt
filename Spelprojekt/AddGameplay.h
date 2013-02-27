#ifndef ADDGAMEPLAY
#define ADDGAMEPLAY
#include "Event.h"
#include "StateManager.h"
#include "Gameplay.h"
#include "Countdown.h"
class AddGameplay : public Event{

public:

	AddGameplay(){}
	~AddGameplay(){}
	virtual void update(){
		StateManager::getInst().popState();
		StateManager::getInst().addState(new Gameplay);
		StateManager::getInst().addState(new Countdown);
	}

};

#endif 