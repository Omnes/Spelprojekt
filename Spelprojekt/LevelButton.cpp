#include "LevelButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "LevelManager.h"

LevelButton::LevelButton(sf::Vector2f pos, std::string evt, std::string img, std::string level) : mPosition(pos), mEvent(evt), mImage(img), mCurrentImage(0), mLevel(level){
	mTexture = *(ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture.getSize().x/3, mTexture.getSize().y);
		mSprite.setTextureRect(mRectangle);

}

LevelButton::~LevelButton(){

}


void LevelButton::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
	if(mSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))){		
	
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ 
	
			mCurrentImage=2;
			LevelManager::getInst().setFilePath(mLevel);
			EventManager::getInst().addEvent(mEvent);
			
		}		
	}

	else{

		mCurrentImage=0;
	}

	mRectangle.left = mRectangle.width*mCurrentImage;
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& LevelButton::getSprite(){

	return mSprite;
}

