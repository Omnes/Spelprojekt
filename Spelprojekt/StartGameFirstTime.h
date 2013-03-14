#ifndef STARTGAMEFIRSTTIME
#define STARTGAMEFIRSTTIME
#include "Event.h"
#include "StateManager.h"
#include "LevelTutorial.h"
#include "WorldMap.h"
#include <iostream>

class StartGameFirstTime : public Event{

public:

	StartGameFirstTime() : mTutorial(false){}
	~StartGameFirstTime(){}

	virtual void update(){

		readSave();

		saveToFile();

		StateManager::getInst().addState(new WorldMap);

		tinyxml2::XMLDocument docSettings;
		docSettings.LoadFile("Resources/Data/Settings.xml");

		if(mTutorial == false && docSettings.FirstChildElement("Tutorial")->BoolAttribute("play") == false){
			StateManager::getInst().addState(new LevelTutorial);
		}
	
	}
	
	void readSave(){

		tinyxml2::XMLDocument doc;

		doc.LoadFile("Resources/Data/Save/SavedGame.xml");

		if(doc.FirstChildElement("Tutorial")){
			mTutorial = doc.FirstChildElement("Tutorial")->BoolAttribute("Tactic");
		}
	}

	void saveToFile(){
		tinyxml2::XMLDocument doc;
			
		doc.LoadFile("Resources/Data/Save/SavedGame.xml");

		if(!doc.FirstChildElement("Tutorial")){
			tinyxml2::XMLElement *tutorial = doc.NewElement("Tutorial");
			if(!tutorial->Attribute("Tactic")){
				tutorial->SetAttribute("Tactic", false);
				doc.LinkEndChild(tutorial);				
			}
		}

		doc.SaveFile("Resources/Data/Save/SavedGame.xml");
	}

private:
	bool mTutorial;

};

#endif 
