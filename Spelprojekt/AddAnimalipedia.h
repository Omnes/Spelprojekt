#ifndef ADDANIMALIPEDIA
#define ADDANIMALIPEDIA
#include "Event.h"
#include "StateManager.h"
#include "Animalipedia.h"

class AddAnimalipedia : public Event{

public:

	AddAnimalipedia(){}
	~AddAnimalipedia(){}
	virtual void update(){StateManager::getInst().addState(new Animalipedia);}

};

#endif 