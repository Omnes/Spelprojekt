#include "AnimalipediaButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "Animalipedia.h"


AnimalipediaButton::AnimalipediaButton(sf::Vector2f pos, std::string page, std::string title, std::string sound, Animalipedia* wiki) 
	: mPosition(pos)
	, mCurrentImage(0)
	, mInfo(page)
	, mTitle(title)
	, mWiki(wiki){
	mTexture = (ResourceManager::getInst().getTexture("Resources/Menu/Animalipedia/text_knapp.png"));
	mSprite.setTexture(*mTexture);
	mSprite.setPosition(mPosition);
	mTitle.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture->getSize().x/3, mTexture->getSize().y);
	mSprite.setTextureRect(mRectangle);
	mSoundBuffer = (ResourceManager::getInst().getSoundBuffer(sound));
	mSound.setBuffer(*mSoundBuffer);
	mSound.setLoop(false);



}

AnimalipediaButton::~AnimalipediaButton(){

}


void AnimalipediaButton::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());
	
	if(mSprite.getGlobalBounds().contains(mousePosition) && mLocked > 0){		
	
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) ){ 
			mCurrentImage=2;
			mWiki->setInfo(mInfo);
		}		
	}

	else{

		mCurrentImage=0;
	}

	if(mWiki->getInfo() == mInfo){
	
		mCurrentImage = 2;	
	}

	mRectangle.left = mRectangle.width*mCurrentImage;
	mSprite.setTextureRect(mRectangle);
}

void AnimalipediaButton::render(){

	sf::RenderWindow *window = WindowManager::getInst().getWindow();

	window->draw(mSprite);
	window->draw(mTitle);
}

void AnimalipediaButton::setLocked(int level){
	mLocked = level;
}

void AnimalipediaButton::setNewInfo(bool boolean){
	mNewInfo = boolean;
}

void AnimalipediaButton::setPosition(sf::Vector2f pos){
	mPosition = pos;
	mSprite.setPosition(mPosition);
	mTitle.setPosition(mPosition);
}