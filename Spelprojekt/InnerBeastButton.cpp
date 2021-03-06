#include "InnerBeastButton.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "ActiveLayer.h"
#include "Entity.h"
#include "Gui.h"
#include <SFML\Graphics\CircleShape.hpp>
#include "ResourceManager.h"
#include "SoundManager.h"

InnerBeastButton::InnerBeastButton(sf::Vector2f position, std::string texture,float cooldown,float speedincrease, float duration, std::string soundFX, Gui* gui)
	: mTexture(ResourceManager::getInst().getTexture(texture))
	, mFrames(3)
	, mCooldown(cooldown)
	, mClickCooldown(150)
	, mGui(gui)
	, mClicked(false)
	, mSpeedIncrease(speedincrease)
	, mSpeedDuration(duration)
	, mSoundFX(*ResourceManager::getInst().getSoundBuffer(soundFX)){

		mSprite.setPosition(position);
		mSprite.setTexture(*mTexture);

		mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y)); //<--- texture rect


		/*mArrows.push_back(InnerBeastArrow(sf::Vector2f(100, yPositions[0]), "Resources/GUI/pil.png"));
		mArrows.push_back(InnerBeastArrow(sf::Vector2f(100, yPositions[1]), "Resources/GUI/pil.png"));
		mArrows.push_back(InnerBeastArrow(sf::Vector2f(100, yPositions[2]), "Resources/GUI/pil.png"));
		*/
		mAnimations.push_back(new Animation(ResourceManager::getInst().getTexture("Resources/GUI/pil.png"), 100, 10, 1));
		mAnimations.push_back(new Animation(ResourceManager::getInst().getTexture("Resources/GUI/pil.png"), 100, 10, 1));
		mAnimations.push_back(new Animation(ResourceManager::getInst().getTexture("Resources/GUI/pil.png"), 100, 10, 1));
}

InnerBeastButton::~InnerBeastButton(){

	while(!mAnimations.empty()){
		delete mAnimations.back();
		mAnimations.pop_back();
	}
}

void InnerBeastButton::update(){

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

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
		for(int i = 0; i< mAnimations.size(); i++){
			
			//N�r vi har klickat p� en pil
			if(mAnimations[i]->getSprite()->getGlobalBounds().contains(mousePosition)){

				SoundManager::getInst().play(mSoundFX);

				std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
				for(std::vector <Entity*>::iterator j = entityVector->begin(); j != entityVector->end(); j++){
					
					if((*j)->getID() == "Animal" && (*j)->getPos().y == mAnimations[i]->getSprite()->getPosition().y){

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

	

	

	if(mClicked){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*1,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		for(int i = 0; i<mAnimations.size(); i++){

			mAnimations[i]->update();
		}
	}

	if(mSpeedTimer.getElapsedTime().asSeconds() > mSpeedDuration){

		while(!mAnimals.empty()){
			mAnimals.back()->setSpeedIncrease(1);
			mAnimals.pop_back();
		}
	}

	if(mCooldownTimer.getElapsedTime().asSeconds() < mCooldown){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*2,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}
}


sf::Sprite* InnerBeastButton::getSprite(){
	//robins fel att det ser ut s�h�r.

	std::vector<float> yPositions = LevelManager::getInst().getLevelsOnLevel();
	sf::RenderWindow* window =  WindowManager::getInst().getWindow();
	if(mClicked){
		for(int i = 0; i<mAnimations.size(); i++){

			mAnimations[i]->setPosition(sf::Vector2f(100,yPositions[i]));
			window->draw(*mAnimations[i]->getSprite());
		}
	}

	return &mSprite;
}

void InnerBeastButton::setClicked(bool boolean){
	mClicked = boolean;
}