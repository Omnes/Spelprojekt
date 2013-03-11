#include "ApplyOptionsButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "OptionsMeny.h"


ApplyOptionsButton::ApplyOptionsButton(sf::Vector2f pos,std::string img, std::string sound,OptionsMeny* options) 
	: mPosition(pos) 
	, mCurrentImage(0)
	, mClickCooldown(300)
	, mFrames(3)
	, mOptionsMenu(options){

	mTex = (ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(*mTex);
	mSprite.setPosition(mPosition);
	mSprite.setTextureRect(sf::IntRect(0,0,mTex->getSize().x/mFrames,mTex->getSize().y));
	mSound.setBuffer(*ResourceManager::getInst().getSoundBuffer(sound));

}

ApplyOptionsButton::~ApplyOptionsButton(){

}


void ApplyOptionsButton::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());
	
	if(mSprite.getGlobalBounds().contains(mousePosition)){		
	
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown){ 
			mClickCooldownTimer.restart();
			mOptionsMenu->saveSettings();
			SoundManager::getInst().loadSettings();
		}		
	}

	else{

		mCurrentImage=0;
	}

	float left = mTex->getSize().x/mFrames * mCurrentImage;
	mSprite.setTextureRect(sf::IntRect(left,0,mTex->getSize().x/mFrames,mTex->getSize().y));
}

sf::Sprite& ApplyOptionsButton::getSprite(){

	return mSprite;
}

