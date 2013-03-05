#ifndef ADDCUTSCENE_1
#define ADDCUTSCENE_1

#include "Event.h"
#include "StateManager.h"
#include "Cutscene.h"

class AddCutscene_1 : public Event{

public:

	AddCutscene_1(){}
	~AddCutscene_1(){}
	virtual void update(){
		StateManager::getInst().addState(new Cutscene("Resources/Data/Cutscenes/Cutscene_1.xml"));
	}

};

#endif