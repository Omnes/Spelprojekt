#include "StateManager.h"
#include "Gameplay.h"
#include "StartMeny.h"
#include <iostream>

StateManager::StateManager(){
	mStateMap["gameplay"] = new Gameplay();
	mStateMap["startmenu"] = new StartMeny();
}

StateManager::~StateManager(){

}

StateManager& StateManager::getInst(){

	static StateManager instance;
	return instance;
}

void StateManager::popState(){

	if(!mStates.empty()){

		mStates.pop();
	}
}

void StateManager::update(){

	mStates.top()->update();
}

void StateManager::render(){

	mStates.top()->render();
}

void StateManager::addState(std::string state){
	
	StateMap::iterator i;
	i = mStateMap.find(state);
	
	if(i == mStateMap.end()){
		std::cout << std::endl << "Denna state hittades inte: " << state;
		return;
	}
	
	mStates.push(i->second);
}