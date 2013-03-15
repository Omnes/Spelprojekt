#include "Button.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "SoundManager.h"


Button::Button(sf::Vector2f pos, std::string evt, std::string img, std::string sound) : 
		mPosition(pos), 
		mEvent(evt), 
		mCurrentImage(0), 
		mPartSystem("Leaf",100),
		mButtonTime(0.3),
		mPressed(false){

		mTexture = (ResourceManager::getInst().getTexture(img));
		mSprite.setTexture(*mTexture);
		mSprite.setPosition(mPosition);
		mRectangle = sf::IntRect(0,0, mTexture->getSize().x/3, mTexture->getSize().y);
		mSprite.setTextureRect(mRectangle);
		mSoundBuffer = (ResourceManager::getInst().getSoundBuffer(sound));
		mSound.setBuffer(*mSoundBuffer);
		mEmitter.setPosition(mPosition);

}

Button::~Button(){

}


void Button::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());
	
	//om musen �r ovanf�rknappen
	if(mSprite.getGlobalBounds().contains(mousePosition) && !mPressed){		
	
		mEmitter.burst(mPartSystem,sf::FloatRect(0,0,mRectangle.width,mRectangle.height),1);
		mCurrentImage=1;

		//om knappen trycks ned
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ 
			mTimer.restart();

			SoundManager::getInst().play(mSound);
			mPressed = true;
		}		
	}

	else{

		mCurrentImage=0;
	}

	if(mPressed){

		mCurrentImage=2;

		if(mTimer.getElapsedTime().asSeconds() > mButtonTime){
			mPressed = false;
			EventManager::getInst().addEvent(mEvent);
		}
	}

	mRectangle.left = mRectangle.width*mCurrentImage;
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& Button::getSprite(){

	return mSprite;
}

