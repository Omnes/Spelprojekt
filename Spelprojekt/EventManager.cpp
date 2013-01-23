#include "EventManager.h"

EventManager::EventManager(){}

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