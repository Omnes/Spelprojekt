#ifndef ADDCUTSCENE_3
#define ADDCUTSCENE_3

#include "Event.h"
#include "StateManager.h"
#include "Cutscene.h"

class AddCutscene_3 : public Event{

public:
	AddCutscene_3(){}
	~AddCutscene_3(){}
	virtual void update(){
		StateManager::getInst().addState(new Cutscene("Resources/Data/Cutscenes/Cutscene_3.xml"));
	}

};

#endif