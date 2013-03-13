#ifndef ADDCUTSCENE_4
#define ADDCUTSCENE_4

#include "Event.h"
#include "StateManager.h"
#include "Cutscene.h"

class AddCutscene_4 : public Event{

public:
	AddCutscene_4(){}
	~AddCutscene_4(){}
	virtual void update(){
		StateManager::getInst().addState(new Cutscene("Resources/Data/Cutscenes/Cutscene_ending.xml"));
	}

};

#endif