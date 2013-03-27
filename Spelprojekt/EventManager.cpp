#include "EventManager.h"
#include "ExitGame.h"
#include "AddMap.h"
#include "AddOptions.h"
#include "AddTaktik.h"
#include "AddGameplay.h"
#include "AddStartMeny.h"
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
#include "AddCutscene_2.h"
#include "AddCutscene_3.h"
#include "AddCutscene_4.h"
#include "AddCutscene_5.h"
#include "StartNewGame.h"
#include "AddTutorial.h"


EventManager::EventManager(){

	mEventMap["exitGame"]= new ExitGame();
	mEventMap["addMap"]= new AddMap();
	mEventMap["addOptions"]= new AddOptions();
	mEventMap["addTaktik"]= new AddTaktik();
	mEventMap["addStart"]= new AddStartMeny();
	mEventMap["addGameplay"]= new AddGameplay();
	mEventMap["popState"] = new PopState();
	mEventMap["addLevelFinished"] = new AddLevelFinished();
	mEventMap["addGameOver"] = new AddGameOver();
	mEventMap["addAnimalipedia"] = new AddAnimalipedia();
	mEventMap["goBackToWorld"] = new GoBackToWorld();
	mEventMap["popStateTwice"] = new PopStateTwice();
	mEventMap["retry"] = new Retry();
	mEventMap["goBackToStartFromOptions"] = new GoBackToStartFromOptions();
	mEventMap["startGameFirstTime"] = new StartGameFirstTime();
	mEventMap["cutscene_intro"] = new AddCutscene_1();
	mEventMap["cutscene_2"] = new AddCutscene_2();
	mEventMap["cutscene_3"] = new AddCutscene_3();
	mEventMap["cutscene_ending"] = new AddCutscene_4();
	mEventMap["cutscene_credits"] = new AddCutscene_5();
	mEventMap["startNewGame"] = new StartNewGame();
	mEventMap["addTutorial"] = new AddTutorial();

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