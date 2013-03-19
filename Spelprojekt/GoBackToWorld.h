#ifndef GOBACKTOWORLD
#define GOBACKTOWORLD
#include "Event.h"
#include "StateManager.h"
#include "StartMeny.h"
#include "WorldMap.h"
#include "LevelManager.h"
#include "GameOver.h"
#include "WorldMapTutorial.h"
#include "AchievementState.h"

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
		tinyxml2::XMLDocument docSave;
		docSave.LoadFile("Resources/Data/Save/SavedGame.xml");

		tinyxml2::XMLDocument docSetting;
		docSetting.LoadFile("Resources/Data/Settings.xml");

		if(docSave.FirstChildElement("Tutorial")->BoolAttribute("World") == false && docSetting.FirstChildElement("Tutorial")->BoolAttribute("play") == false){
			StateManager::getInst().addState(new WorldMapTutorial);
		}else{
			StateManager::getInst().addState(new AchievementState(worldMap->getSection()));
			if(worldMap->getNewWorld()){
				worldMap->doCutscene();
			}
		}
	}
};
 

#endif 