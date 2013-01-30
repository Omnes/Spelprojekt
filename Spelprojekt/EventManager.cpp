#include "EventManager.h"
#include "ExitGame.h"
#include "AddMap.h"
#include "AddOptions.h"
#include "AddTaktik.h"

EventManager::EventManager(){

	mEventMap["exitGame"]= new ExitGame();
	mEventMap["addMap"]= new AddMap();
	mEventMap["addOptions"]= new AddOptions();
	mEventMap["addTaktik"]= new AddTaktik();


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