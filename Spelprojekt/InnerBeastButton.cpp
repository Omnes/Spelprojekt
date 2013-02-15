#include "InnerBeastButton.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "ActiveLayer.h"
#include "Entity.h"
#include "Gui.h"
#include <SFML\Graphics\CircleShape.hpp>

InnerBeastButton::InnerBeastButton(sf::Vector2f position, std::string texture, Gui* gui)
	: mTexture(ResourceManager::getInst().getTexture(texture))
	, mFrames(4)
	, mCooldown(10)
	, mClickCooldown(150)
	, mGui(gui)
	, mClicked(false)
	, mSpeedIncrease(2)
	, mSpeedDuration(5){

		mSprite.setPosition(position);
		mSprite.setTexture(*mTexture);

		mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y)); //<--- texture rect
		mArrows.push_back(InnerBeastArrow(sf::Vector2f(100, 200), "Resources/Misc/knapp1.jpg"));
		mArrows.push_back(InnerBeastArrow(sf::Vector2f(100, 400), "Resources/Misc/knapp2.jpg"));
		mArrows.push_back(InnerBeastArrow(sf::Vector2f(100, 600), "Resources/Misc/knapp3.jpg"));
}

InnerBeastButton::~InnerBeastButton(){}

void InnerBeastButton::update(){

	sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition(*WindowManager::getInst().getWindow());

	//Innerbeastknapp
	mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	//om musen �r �ver
	if(mSprite.getGlobalBounds().contains(mousePosition) && !mClicked){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		//om vi klickat �ver fyrkanten
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown && mCooldownTimer.getElapsedTime().asSeconds() > mCooldown){
			mGui->unclickAll();
			setClicked(true);
			mClickCooldownTimer.restart();
		}
	}

	
	//PilKnappar
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
		&& mClicked 
		&& mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown 
		&& mCooldownTimer.getElapsedTime().asSeconds() > mCooldown){

		mGui->unclickAll();	
		mClickCooldownTimer.restart();
		for(int i = 0; i< mArrows.size(); i++){
			
			//N�r vi har klickat p� en pil
			if(mArrows[i].getSprite().getGlobalBounds().contains(mousePosition)){

				std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
				for(std::vector <Entity*>::iterator j = entityVector->begin(); j != entityVector->end(); j++){
					
					if((*j)->getID() == "Animal" && (*j)->getPos().y == mArrows[i].getSprite().getPosition().y){

						Animal* animal = dynamic_cast<Animal*>(*j);
						mAnimals.push_back(animal);
						animal->setSpeedIncrease(mSpeedIncrease);
						mSpeedTimer.restart();
						mCooldownTimer.restart();
					}
				}
			}
		}
	}

	

	if(mCooldownTimer.getElapsedTime().asMilliseconds() < mCooldown){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*3,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}

	if(mClicked){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*2,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		for(int i = 0; i<mArrows.size(); i++){

			mArrows[i].update();
		}
	}

	if(mSpeedTimer.getElapsedTime().asSeconds() > mSpeedDuration){

		while(!mAnimals.empty()){
			mAnimals.back()->setSpeedIncrease(1);
			mAnimals.pop_back();
		}
	}
}


sf::Sprite* InnerBeastButton::getSprite(){
	//robins fel att det ser ut s�h�r.
	sf::RenderWindow* window =  WindowManager::getInst().getWindow();
	if(mClicked){
		for(int i = 0; i<mArrows.size(); i++){

			window->draw(mArrows[i].getSprite());
		}
	}

	return &mSprite;
}

void InnerBeastButton::setClicked(bool boolean){
	mClicked = boolean;
}