#include "LevelButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "LevelManager.h"
#include "GlobalButtonTimer.h"

LevelButton::LevelButton(sf::Vector2f pos, std::string evt, std::string img, std::string level) 
	: mPosition(pos)
	, mEvent(evt)
	, mImage(img)
	, mCurrentImage(0)
	, mLevel(level)
	, mAlive(true)
	, mActive(false){
	mTexture = *(ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture.getSize().x/3, mTexture.getSize().y); //Rekten ska ha rätt bredd
	mSprite.setTextureRect(mRectangle);
}

LevelButton::~LevelButton(){

}


void LevelButton::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

	//mAlive står här. ändra om du behöver
	if(mActive == true && mAlive == true && mSprite.getGlobalBounds().contains(mousePosition)){		
	
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && GlobalButtonTimer::onCoolDown()){ 
			
			
				//mCurrentImage=2;
				LevelManager::getInst().setFilePath(mLevel);
				EventManager::getInst().addEvent(mEvent);

				GlobalButtonTimer::globalRestart();
		}		
	}else if(mActive == false && mAlive == true){
		mCurrentImage = 0;
	}else if(mAlive == false){
		mCurrentImage = 2;
	}else{
		mCurrentImage = 0;
	}

	mRectangle.left = mRectangle.width*mCurrentImage; // kommentera in den här när vi har en lämplig bild
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

}

bool LevelButton::getActive(){
	return mActive;
}

void LevelButton::setActive(bool active){
	mActive = active;

}