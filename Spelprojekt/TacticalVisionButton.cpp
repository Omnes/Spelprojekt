#include "TacticalVisionButton.h"
#include <SFML\Window\Mouse.hpp>
#include "ResourceManager.h"
#include "WindowManager.h"
#include "StateManager.h"
#include "TacticalVision.h"

TacticalVisionButton::TacticalVisionButton(sf::Vector2f position, std::string texture, Gui* gui) 
	: mTexture(ResourceManager::getInst().getTexture(texture))
	, mGui(gui)
	, mClicked(false)
	, mFrames(4)
	, mCooldown(10)
	, mClickCooldown(){
		mCooldownTimer.restart();
		mSprite.setTexture(*mTexture);
		mSprite.setPosition(position);
		mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames, mTexture->getSize().y));
}

TacticalVisionButton::~TacticalVisionButton(){

}

void TacticalVisionButton::activateTac(){

	StateManager::getInst().addState(new TacticalVision);
	mCooldownTimer.restart();

}

void TacticalVisionButton::update(){
	
	sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition(*WindowManager::getInst().getWindow());

	mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	//om musen �r �ver
	if(mSprite.getGlobalBounds().contains(mousePosition) && mCooldownTimer.getElapsedTime().asSeconds() > mCooldown){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		//om vi klickat �ver fyrkanten
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown){
			activateTac();
			mClickCooldownTimer.restart();
			mGui->unclickAll();
		}
	}
}


sf::Sprite* TacticalVisionButton::getSprite(){

	return &mSprite;
}

void TacticalVisionButton::setClicked(bool boolean){

	mClicked = boolean;
}