#include "WaitState.h"

WaitState::WaitState(std::string evt):
	mEvent(evt)
{

}

WaitState::~WaitState(){}

void WaitState::render(){}

void WaitState::update(){
	std::string evt = mEvent; 
	StateManager::getInst().popState();
	EventManager::getInst().addEvent(evt);
}

std::string WaitState::getMusic(){
	return "";
}