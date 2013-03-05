#include "EventManager.h"
#include "ExitGame.h"
#include "AddMap.h"
#include "AddOptions.h"
#include "AddTaktik.h"
#include "AddGameplay.h"
#include "AddStartMeny.h"
#include "AddPause.h"
#include "PopState.h"
#include "AddLevelFinished.h"
#include "addGameOver.h"
#include "AddAnimalipedia.h"
#include "GoBackToWorld.h"
#include "PopStateTwice.h"
#include "Retry.h"
#include "GoBackToStartFromOptions.h"
#include "StartGameFirstTime.h"
#include "AddCutscene_1.h"

EventManager::EventManager(){

	mEventMap["exitGame"]= new ExitGame();
	mEventMap["addMap"]= new AddMap();
	mEventMap["addOptions"]= new AddOptions();
	mEventMap["addTaktik"]= new AddTaktik();
	mEventMap["addStart"]= new AddStartMeny();
	mEventMap["addGameplay"]= new AddGameplay();
	mEventMap["popState"] = new PopState();
	mEventMap["addPause"] = new AddPause();
	mEventMap["addLevelFinished"] = new AddLevelFinished();
	mEventMap["addGameOver"] = new AddGameOver();
	mEventMap["addAnimalipedia"] = new AddAnimalipedia();
	mEventMap["goBackToWorld"] = new GoBackToWorld();
	mEventMap["popStateTwice"] = new PopStateTwice();
	mEventMap["retry"] = new Retry();
	mEventMap["goBackToStartFromOptions"] = new GoBackToStartFromOptions();
	mEventMap["startGameFirstTime"] = new StartGameFirstTime();
	mEventMap["cutscene_1"] = new AddCutscene_1();

}

EventManager::~EventManager(){}

EventManager& EventManager::getInst(){
	static EventManager EM;
	return EM;
}

void EventManager::addEvent(std::string eventName){
	EventMap::iterator i;
	i = mEventMap.find(eventName);
	
	if(i != mEventMap.end()){
		mEventStack.push(i->second);
	}else{
		std::cout<<"Event is empty"<<std::endl;
	}
}

void EventManager::update(){
	while(!mEventStack.empty()){
		mEventStack.top()->update();
		mEventStack.pop();
	}
}