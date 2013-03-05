#ifndef STARTGAMEFIRSTTIME
#define STARTGAMEFIRSTTIME
#include "Event.h"
#include "StateManager.h"
#include "LevelTutorial.h"
#include "WorldMap.h"
#include <iostream>

class StartGameFirstTime : public Event{

public:

	StartGameFirstTime() : mWorld(0){}
	~StartGameFirstTime(){}

	virtual void update(){

		readSave();

		StateManager::getInst().addState(new WorldMap);

		if(mWorld == 0){
			StateManager::getInst().addState(new Tutorial);
		}
	
	}
	
	void readSave(){
		tinyxml2::XMLDocument doc;

		doc.LoadFile("Resources/Data/Save/SavedGame.xml");

		tinyxml2::XMLElement *world = doc.FirstChildElement("World");

		if(world != 0){
			mWorld = world->FirstAttribute()->IntValue();
		}else{
			std::cout<<"Tutorial har inte körts"<<std::endl;
		}
	}

private:
	int mWorld;


};

#endif 
