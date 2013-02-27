#include "Countdown.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "EventManager.h"
#include <SFML\Window\Keyboard.hpp>

Countdown::Countdown()
	: mRenderState(0)
	, mCurrentNumber(0){
	mRenderState = StateManager::getInst().getTop();
	mMusic = mRenderState->getMusic();
	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Misc/Countdown.png"));
	mRect = sf::IntRect(0,0,mSprite.getTexture()->getSize().x/3,mSprite.getTexture()->getSize().y);
	mSprite.setTextureRect(sf::IntRect(mRect));
	mCountdown.restart();
	mAnimationTimer.restart();
}

Countdown::~Countdown(){

}

//se till att den är relativ till view! GJORT!!!!!
void Countdown::render(){
	if(mRenderState != 0){
		mRenderState->render();
	}

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	window->draw(mSprite);
}

void Countdown::update(){

	if(mAnimationTimer.getElapsedTime().asSeconds() > 1){

		mCurrentNumber +=1;
		mAnimationTimer.restart();
	}
		if (mCountdown.getElapsedTime().asSeconds() > 3){
		EventManager::getInst().addEvent("popState");
	}

		mRect.left = mRect.width*mCurrentNumber;
		mSprite.setTextureRect(mRect);
}

std::string Countdown::getMusic(){
	return mMusic;
}
