#include "PauseMeny.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"

PauseMeny::PauseMeny(): mRenderState(0){
	mRenderState = StateManager::getInst().getTop();
	mSprite.setTexture(*ResourceManager::getInst().getTexture("paused.png"));
}

PauseMeny::~PauseMeny(){

}


void PauseMeny::render(){
	if(mRenderState != 0){
		mRenderState->render();
	}
	WindowManager::getInst().getWindow()->draw(mSprite);
	
}

void PauseMeny::update(){
	

}

States* PauseMeny::createNew(){
	return new PauseMeny;
}