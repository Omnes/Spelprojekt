#include "TacticalVision.h"
#include "StateManager.h"
#include "WindowManager.h"

TacticalVision::TacticalVision() 
	: mRenderState(0){
	mRenderState = StateManager::getInst().getTop();
	mTimer.restart();
}

TacticalVision::~TacticalVision(){

}

void TacticalVision::update(){

	if(mTimer.getElapsedTime().asSeconds() > 5){

		StateManager::getInst().popState();
	}
}
	
void TacticalVision::render(){

		if(mRenderState != 0){
		mRenderState->render();
	}

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
}