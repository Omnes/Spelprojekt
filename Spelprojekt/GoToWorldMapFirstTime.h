#ifndef GOTOWORLDMAPFIRSTTIME
#define GOTOWORLDMAPFIRSTTIME
#include "Event.h"
#include "StateManager.h"
#include "WorldMapTutorial.h"
#include "WorldMap.h"

class GoToWorldMapFirstTime : public Event{

public:

	GoToWorldMapFirstTime(){}
	~GoToWorldMapFirstTime(){}
	virtual void update(){
		StateManager::getInst().popState();
		WorldMap* worldMap = dynamic_cast<WorldMap*>(StateManager::getInst().getTop());
		GameOver::sRetryCount = 0;
		worldMap->setDeadAnimals(LevelManager::getInst().getDeadAnimals());
		worldMap->setCurrentWorldOrSub(LevelManager::getInst().getFilePath());
		worldMap->readNewAnimals();
	}

};

#endif 
