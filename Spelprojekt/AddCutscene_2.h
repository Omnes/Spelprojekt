#ifndef ADDCUTSCENE_2
#define ADDCUTSCENE_2

#include "Event.h"
#include "StateManager.h"
#include "Cutscene.h"

class AddCutscene_2 : public Event{

public:
	AddCutscene_2(){}
	~AddCutscene_2(){}
	virtual void update(){
		StateManager::getInst().addState(new Cutscene("Resources/Data/Cutscenes/Cutscene_2.xml"));
	}

};

#endif