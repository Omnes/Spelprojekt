#ifndef ADDTUTORIAL
#define ADDTUTORIAL

#include "LevelTutorial.h"
#include "Event.h"


class AddTutorial :  public Event{
public:
	AddTutorial(){}
	~AddTutorial(){}
	virtual void update(){
		StateManager::getInst().addState(new LevelTutorial);
	}


};

#endif