#include "LevelButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "LevelManager.h"

LevelButton::LevelButton(sf::Vector2f pos, std::string evt, std::string img, std::string level) 
	: mPosition(pos)
	, mEvent(evt)
	, mImage(img)
	, mCurrentImage(0)
	, mLevel(level)
	, mAlive(true){
	mTexture = *(ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture.getSize().x/1, mTexture.getSize().y); //Rekten ska ha rätt bredd
	mSprite.setTextureRect(mRectangle);

}

LevelButton::~LevelButton(){

}


void LevelButton::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();


	//mAlive står här. ändra om du behöver
	if(mAlive  && mSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))){		
	
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

	//mRectangle.left = mRectangle.width*mCurrentImage; // kommentera in den här när vi har en lämplig bild
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& LevelButton::getSprite(){

	return mSprite;
}

std::string LevelButton::getLevel(){
	return mLevel;
}

bool LevelButton::getAlive(){
	return mAlive;
}

void LevelButton::setAlive(bool alive){
	mAlive = alive;

	//ändra bild här <------------------------------

}