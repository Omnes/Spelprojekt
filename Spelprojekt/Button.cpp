#include "Button.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"


Button::Button(sf::Vector2f pos, std::string evt, std::string img, std::string sound) : mPosition(pos), mEvent(evt), mCurrentImage(0), mPartSystem("ButtonEffekt",100){
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

Button::~Button(){

}


void Button::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());
	
	if(mSprite.getGlobalBounds().contains(mousePosition)){		
	
		mEmitter.burst(mPartSystem,sf::FloatRect(0,0,66,150),1);
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ 
			mCurrentImage=2;
			EventManager::getInst().addEvent(mEvent);
		}		
	}

	else{

		mCurrentImage=0;
	}

	mRectangle.left = mRectangle.width*mCurrentImage;
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& Button::getSprite(){

	return mSprite;
}

