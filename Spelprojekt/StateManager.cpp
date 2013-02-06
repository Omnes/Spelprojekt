#include "StateManager.h"
#include "Gameplay.h"
#include "StartMeny.h"
#include "WorldMap.h"
#include "OptionsMeny.h"
#include "Taktikmeny.h"
#include <iostream>
#include "PauseMeny.h"
#include "LevelFinished.h"

StateManager::StateManager(){
	
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

void StateManager::addState(States* state){
	
	mStates.push(state);
}

States* StateManager::getTop(){
	if(!mStates.empty())
		return mStates.top();
	return 0;
}