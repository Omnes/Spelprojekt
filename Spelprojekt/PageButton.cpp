#include "PageButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "Animalipedia.h"




PageButton::PageButton(sf::Vector2f pos,int flipNumber,std::string img, std::string sound, Animalipedia* wiki) 
	: mPosition(pos)
	, mCurrentImage(0)
	, mFlipNumber(flipNumber){
	mTexture = (ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(*mTexture);
	mSprite.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture->getSize().x/3, mTexture->getSize().y);
	mSprite.setTextureRect(mRectangle);
	mSoundBuffer = (ResourceManager::getInst().getSoundBuffer(sound));
	mSound.setBuffer(*mSoundBuffer);
	mSound.setLoop(false);

	mWiki = wiki;


}

PageButton::~PageButton(){

}


void PageButton::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());
	
	if(mSprite.getGlobalBounds().contains(mousePosition)){		
	
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldown.getElapsedTime().asMilliseconds() > 500){
			mClickCooldown.restart();
			mCurrentImage=2;
			mWiki->setPage(mWiki->getPage() + mFlipNumber);

		}		
	}

	else{

		mCurrentImage=0;
	}

	mRectangle.left = mRectangle.width*mCurrentImage;
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& PageButton::getSprite(){

	return mSprite;
}

