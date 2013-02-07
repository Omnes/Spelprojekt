#include "PauseMeny.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"

PauseMeny::PauseMeny(): mRenderState(0), mResumeButton(sf::Vector2f(640,480),"addTaktik","knapp1.jpg", "Resources/Sound/test.wav"){
	mRenderState = StateManager::getInst().getTop();
	mSprite.setTexture(*ResourceManager::getInst().getTexture("paused.png"));
}

PauseMeny::~PauseMeny(){

}

//se till att den är relativ till view! GJORT!!!!!
void PauseMeny::render(){
	if(mRenderState != 0){
		mRenderState->render();
	}

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
	WindowManager::getInst().getWindow()->draw(mSprite);
	WindowManager::getInst().getWindow()->draw(mResumeButton.getSprite());

	
}

void PauseMeny::update(){
	mResumeButton.update();

}
