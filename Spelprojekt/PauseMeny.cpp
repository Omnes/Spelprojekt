#include "PauseMeny.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "EventManager.h"
#include <SFML\Window\Keyboard.hpp>

PauseMeny::PauseMeny(): mRenderState(0), mResumeButton(sf::Vector2f(640,480),"popState","Resources/Misc/knapp1.jpg", "Resources/Sound/test.wav"){
	mRenderState = StateManager::getInst().getTop();
	mMusic = mRenderState->getMusic();
	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/PauseMenu/paused.png"));
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		EventManager::getInst().addEvent("popStateTwice");
	}
}

std::string PauseMeny::getMusic(){
	return mMusic;
}
