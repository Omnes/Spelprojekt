#include "TacticMenuButton.h"
#include "TaktikMeny.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "AnimalPrototype.h"


TacticMenuButton::TacticMenuButton(sf::Vector2f pos, TaktikMeny* tacticMenu, std::string img, std::string sound) : 

	mPosition(pos),
	mCurrentImage(0),
	mPartSystem("ButtonEffekt",100),
	mTaktikMeny(tacticMenu)
{
	
		
		
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
	
	//kan sätta denna framför mSprite.getGlobalBounds().... för att få bättre 
	// visuell feedback att alla spots är tagna
	if(mTaktikMeny->getFreeSpots() == false){

		mCurrentImage=1;

		//mTaktikMeny->getAllSpotsTaken() returnar false im det inte finns några lediga spots
		if(mSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))){

			mEmitter.burst(mPartSystem,sf::FloatRect(0,0,66,150),1);
			mCurrentImage=2;

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ 

				mSound.play();

				mTaktikMeny->createAnimals();
				EventManager::getInst().addEvent("addGameplay");
			}

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

