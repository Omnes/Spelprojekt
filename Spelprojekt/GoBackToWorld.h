#ifndef GOBACKTOWORLD
#define GOBACKTOWORLD
#include "Event.h"
#include "StateManager.h"
#include "StartMeny.h"
#include "WorldMap.h"
#include "LevelManager.h"
#include "GameOver.h"

class GoBackToWorld : public Event{

public:

	GoBackToWorld(){}
	~GoBackToWorld(){}
	virtual void update(){
		StateManager::getInst().popState();
		WorldMap* worldMap = dynamic_cast<WorldMap*>(StateManager::getInst().getTop());
		worldMap->saveToFile(LevelManager::getInst().getFilePath());
		GameOver::sRetryCount = 0;
	}

};

#endif 