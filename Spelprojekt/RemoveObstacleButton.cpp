#include "RemoveObstacleButton.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "ActiveLayer.h"
#include "Entity.h"
#include "Gui.h"
#include <SFML\Graphics\CircleShape.hpp>

RemoveObstacleButton::RemoveObstacleButton(std::vector<std::string> obstacle,sf::Vector2f position, std::string texture,float cooldown, std::string particleName, int emittAmount, Gui* gui)
	: mObstacles(obstacle)
	, mTexture(ResourceManager::getInst().getTexture(texture))
	, mFrames(3)
	, mCooldown(cooldown)
	, mClickCooldown(75)
	, mGui(gui)
	, mClicked(false)
	, mParticleSystem(particleName,100)
	, mEmittAmount(emittAmount){

		mSprite.setPosition(position);
		mSprite.setTexture(*mTexture);

		mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y)); //<--- texture rect

}

RemoveObstacleButton::~RemoveObstacleButton(){}

bool RemoveObstacleButton::findID(std::string id){
	for(int i = 0; i < mObstacles.size(); i++){
		if(mObstacles[i] == id){
			return true;
		}
	}
	return false;
}


void RemoveObstacleButton::killRelativePositionEntity(sf::Vector2f mousePosition){
	const sf::View* view = &WindowManager::getInst().getWindow()->getView();
	//sf::Vector2f relativeMousePosition = mousePosition + view->getCenter() - sf::Vector2f(view->getSize().x/2,view->getSize().y/2);
	sf::Vector2f relativeMousePosition = WindowManager::getInst().getWindow()->convertCoords((sf::Vector2i)mousePosition,WindowManager::getInst().getWindow()->getView());

		std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
		//hitta vad vi har musen över och döda den
		for(std::vector<Entity*>::iterator i = entityVector->begin();i != entityVector->end();){
			sf::FloatRect bounds = (*i)->getSprite()->getGlobalBounds();
			bool contains = bounds.contains(relativeMousePosition);

			std::string id = (*i)->getID();

			if(findID(id) && contains){
				mEmitter.setPosition((*i)->getPos());
				mEmitter.burst(mParticleSystem,60,mEmittAmount);
				delete *i;
				i = entityVector->erase(i);
				
			}else{
				i++;
			}
		}

		setClicked(false);
		mCooldownTimer.restart();
		mClickCooldownTimer.restart();
}



void RemoveObstacleButton::update(){

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

	mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	//om musen är över
	if(mSprite.getGlobalBounds().contains(mousePosition)){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		//om vi klickat över fyrkanten
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown){
			mGui->unclickAll();
			setClicked(true);
			mClickCooldownTimer.restart();
		}
	}

	//om vi klickat nånstans
	//kan leda till nån kul bugg i början av banan pga relativ position
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
		&& mClicked 
		&& mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown 
		&& mCooldownTimer.getElapsedTime().asSeconds() > mCooldown){

		killRelativePositionEntity(mousePosition);
	}

	if(mClicked){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*1,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}

	if(mCooldownTimer.getElapsedTime().asMilliseconds() < mCooldown){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*2,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}
}


sf::Sprite* RemoveObstacleButton::getSprite(){

	return &mSprite;
}

void RemoveObstacleButton::setClicked(bool boolean){
	mClicked = boolean;
}