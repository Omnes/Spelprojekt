#include "StateManager.h"
#include "Gameplay.h"
#include "StartMeny.h"
#include "WorldMap.h"
#include "OptionsMeny.h"
#include "Taktikmeny.h"
#include <iostream>
#include "PauseMeny.h"

StateManager::StateManager(){
	mStateMap["gameplay"] = new Gameplay();
	mStateMap["startmenu"] = new StartMeny();
	mStateMap["worldmap"] = new WorldMap();
	mStateMap["optionsmenu"] = new OptionsMeny(); 
	mStateMap["taktikmenu"] = new TaktikMeny();
	mStateMap["pausemenu"] = new PauseMeny();
	
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
	
	mStates.push(i->second->createNew());
}

States* StateManager::getTop(){
	if(!mStates.empty())
		return mStates.top();
	return 0;
}