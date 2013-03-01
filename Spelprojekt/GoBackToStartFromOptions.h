#ifndef GOBACKFROMSTARTFROMOPTIONS
#define GOBACKFROMSTARTFROMOPTIONS
#include "Event.h"
#include "StateManager.h"
#include "WindowManager.h"

class GoBackToStartFromOptions : public Event{

public:

	GoBackToStartFromOptions(){}
	~GoBackToStartFromOptions(){}
	virtual void update(){
		StateManager::getInst().popState();
		WindowManager::getInst().createWindow();
	}

};

#endif 