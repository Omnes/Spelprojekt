#ifndef STARTNEWGAME
#define STARTNEWGAME
#include "Event.h"
#include "StateManager.h"
#include "LevelTutorial.h"
#include "WorldMap.h"
#include <iostream>
#include "WaitState.h"

class StartNewGame : public Event{

public:

	StartNewGame(){}
	~StartNewGame(){}

	virtual void update(){
		saveToFile();

		resetAnimalipedia();

		StateManager::getInst().addState(new WorldMap);

		tinyxml2::XMLDocument docSettings;
		docSettings.LoadFile("Resources/Data/Settings.xml");

		if(docSettings.FirstChildElement("Tutorial")->BoolAttribute("play") == false){
			/*StateManager::getInst().addState(new LevelTutorial);*/
			StateManager::getInst().addState(new WaitState("addTutorial"));
	
		}
		StateManager::getInst().addState(new Cutscene("Resources/Data/Cutscenes/Cutscene_intro.xml"));
		
	}

	void saveToFile(){
		tinyxml2::XMLDocument doc;

		tinyxml2::XMLElement *tutorial = doc.NewElement("Tutorial");

		tutorial->SetAttribute("Tactic", false);
		doc.LinkEndChild(tutorial);

		doc.SaveFile("Resources/Data/Save/SavedGame.xml");
	}

	void resetAnimalipedia(){
	
		tinyxml2::XMLDocument doc;
			
		doc.LoadFile("Resources/Data/Animalipedia/UnlockedFacts.xml");
	
		tinyxml2::XMLElement *elm = doc.FirstChildElement();

		while(elm != 0){
		
			elm->SetAttribute("unlocked", 0);
			elm->SetAttribute("extraUnlocked", 0);
			elm->SetAttribute("newFacts", 0);

			elm = elm->NextSiblingElement();
		}

		doc.SaveFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

	}

private:

};

#endif 
