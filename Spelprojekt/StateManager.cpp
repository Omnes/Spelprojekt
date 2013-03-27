#include "StateManager.h"
#include "Gameplay.h"
#include "StartMeny.h"
#include "WorldMap.h"
#include "OptionsMeny.h"
#include "Taktikmeny.h"
#include <iostream>
#include "LevelFinished.h"
#include "SoundManager.h"

StateManager::StateManager(){
	
}

StateManager::~StateManager(){

}

StateManager& StateManager::getInst(){

	static StateManager instance;
	return instance;
}

void StateManager::popState(){
	std::cout << " <--" << std::endl;
	if(!mStates.empty()){
		delete mStates.top();
		mStates.pop();
	}

	changeMusic();
}

void StateManager::update(){

	mStates.top()->update();
}

void StateManager::render(){

	mStates.top()->render();
}

void StateManager::addState(States* state){
	std::cout << " -->" << std::endl;
	
	mStates.push(state);

	changeMusic();
}

States* StateManager::getTop(){
	if(!mStates.empty())
		return mStates.top();
	return 0;
}

void StateManager::changeMusic(){
	SoundManager* soundManager = &SoundManager::getInst();

	States* topState = getTop();

	float fadeTime = 120;

	if(soundManager->getCurrentPlaying() == 0){
		soundManager->play(topState->getMusic());
	}else if(soundManager->getCurrentPlaying()->getFilepath() != topState->getMusic()){
		soundManager->fadeTo(topState->getMusic(), fadeTime);
	}
}