#include "TacticalVision.h"
#include "StateManager.h"
#include "WindowManager.h"
#include "LayerManager.h"


TacticalVision::TacticalVision() 
	: mRenderState(0)
	, mDuration(6){
	mRenderState = dynamic_cast<Gameplay*>(StateManager::getInst().getTop());
	mTimer.restart();
	mCamera = new TacticalVisionCamera(mRenderState->getLayerManager());
}

TacticalVision::~TacticalVision(){

}

void TacticalVision::update(){

	
	if(mTimer.getElapsedTime().asSeconds() < mDuration-1){

		mCamera->update();
	}else{
		mCamera->moveBackToStartPosition();
	}

	if(mTimer.getElapsedTime().asSeconds() > mDuration){

		StateManager::getInst().popState();
	}
}
	
void TacticalVision::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->setView(*mCamera->getView());


	if(mRenderState != 0){
		mRenderState->renderFromTacVision();
	}

	
	
}