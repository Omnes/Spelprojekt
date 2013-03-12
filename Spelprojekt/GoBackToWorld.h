#ifndef GOBACKTOWORLD
#define GOBACKTOWORLD
#include "Event.h"
#include "StateManager.h"
#include "StartMeny.h"
#include "WorldMap.h"
#include "LevelManager.h"
#include "GameOver.h"
#include "WorldMapTutorial.h"

class GoBackToWorld : public Event{

public:

	//static bool sTutorialPlayed;
	GoBackToWorld(){}
	~GoBackToWorld(){}
	virtual void update(){
		StateManager::getInst().popState();
		WorldMap* worldMap = dynamic_cast<WorldMap*>(StateManager::getInst().getTop());
		GameOver::sRetryCount = 0;
		worldMap->setDeadAnimals(LevelManager::getInst().getDeadAnimals());
		worldMap->setCurrentWorldOrSub(LevelManager::getInst().getFilePath());
		worldMap->readNewAnimals();

		//kanske borde sätta den här ngn annanstans
		tinyxml2::XMLDocument doc;
		doc.LoadFile("Resources/Data/Save/SavedGame.xml");

		if(!doc.FirstChildElement("Tutorial")){
			StateManager::getInst().addState(new WorldMapTutorial);
		}
	}
};
 

#endif 