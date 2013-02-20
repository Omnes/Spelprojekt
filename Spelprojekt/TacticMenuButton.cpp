#include "TacticMenuButton.h"
#include "Taktikmeny.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "AnimalPrototype.h"


TacticMenuButton::TacticMenuButton(sf::Vector2f pos, TaktikMenu* tacticMenu, std::string img, std::string sound) : mPosition(pos), mEvent(evt), mCurrentImage(0), mPartSystem("ButtonEffekt",100){
	mTexture = (ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(*mTexture);
	mSprite.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture->getSize().x/3, mTexture->getSize().y);
	mSprite.setTextureRect(mRectangle);
	mSoundBuffer = (ResourceManager::getInst().getSoundBuffer(sound));
	mSound.setBuffer(*mSoundBuffer);
	mSound.setLoop(false);
	mEmitter.setPosition(mPosition);

}

TacticMenuButton::~TacticMenuButton(){

}


void TacticMenuButton::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
	if(mSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))){		
	
		mEmitter.burst(mPartSystem,sf::FloatRect(0,0,66,150),1);
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ 
	
			mSound.play();
			mCurrentImage=2;
			/*EventManager::getInst().addEvent("gameplay");*/
		}		
	}

	else{

		mCurrentImage=0;
	}

	mRectangle.left = mRectangle.width*mCurrentImage;
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& TacticMenuButton::getSprite(){

	return mSprite;
}

