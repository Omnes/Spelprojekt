#include "LoadButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "LevelManager.h"
#include "GlobalButtonTimer.h"

LoadButton::LoadButton(sf::Vector2f pos, std::string evt, std::string img, std::string sound) 
	: mPosition(pos)
	, mEvent(evt)
	, mImage(img)
	, mCurrentImage(0)
	, mActive(false)
	, mTimer(59)
	, mTimerMax(60)

{

	mTexture = *(ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture.getSize().x/4, mTexture.getSize().y); //Rekten ska ha rätt bredd
	mSprite.setTextureRect(mRectangle);
}

LoadButton::~LoadButton(){

}


void LoadButton::update(){

	

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

	//timer
	mTimer++;

	if(mTimer > mTimerMax){
		setActive();
		mTimer = 0;
	}

	if(mActive && mSprite.getGlobalBounds().contains(mousePosition)){		
	
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && GlobalButtonTimer::onCoolDown()){ 
			
			
				mCurrentImage=2;
				EventManager::getInst().addEvent(mEvent);

				GlobalButtonTimer::globalRestart();
		}		
	}else if(!mActive){
		mCurrentImage=3;
	}else{
		mCurrentImage=0;
	}

	mRectangle.left = mRectangle.width*mCurrentImage; // kommentera in den här när vi har en lämplig bild
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& LoadButton::getSprite(){

	return mSprite;
}

void LoadButton::setActive(){
	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Save/SavedGame.xml");

	if(doc.FirstChildElement("World")){
		if(doc.FirstChildElement("World")->IntAttribute("Worlds") > 0){
			mActive = true;
		}
	}else{
		mActive = false;
	}
}