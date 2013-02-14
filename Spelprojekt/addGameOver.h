#ifndef ADDGAMEOVER
#define ADDGAMEOVER
#include "Event.h"
#include "StateManager.h"
#include "GameOver.h"

class AddGameOver: public Event{
public:

	AddGameOver(){}
	~AddGameOver(){}

	virtual void update(){
		StateManager::getInst().popState();
		StateManager::getInst().addState(new GameOver);
	}


private:

};


#endif