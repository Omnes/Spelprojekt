#include "RemoveObstacleButton.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "ActiveLayer.h"
#include "Entity.h"

RemoveObstacleButton::RemoveObstacleButton(std::string obstacle,sf::Vector2f position, std::string texture)
	: mObstacle(obstacle)
	, mTexture(ResourceManager::getInst().getTexture(texture))
	, mFrames(4)
	, mCooldown(100)
	, mClickCooldown(75){

		mSprite.setPosition(position);
		mSprite.setTexture(*mTexture);

		mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y)); //<--- texture rect

}

RemoveObstacleButton::~RemoveObstacleButton(){}

void RemoveObstacleButton::update(){
	sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition(*WindowManager::getInst().getWindow());

	mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));

	if(mSprite.getGlobalBounds().contains(mousePosition)){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown){
			setClicked(true);
			mClickCooldownTimer.restart();
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClicked && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown && mCooldownTimer.getElapsedTime().asMilliseconds() > mCooldown){
		sf::Vector2f relativeMousePosition = mousePosition + sf::Vector2f(WindowManager::getInst().getWindow()->getView().getCenter().x,0);

		std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();

		for(std::vector<Entity*>::iterator i = entityVector->begin();i != entityVector->end();){
			if((*i)->getID() == mObstacle && (*i)->getSprite()->getGlobalBounds().contains(relativeMousePosition)){
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

	if(mClicked){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*2,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}

	if(mCooldownTimer.getElapsedTime().asMilliseconds() > mCooldown){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*3,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}
}

sf::Sprite* RemoveObstacleButton::getSprite(){
	return &mSprite;
}

void RemoveObstacleButton::setClicked(bool boolean){
	mClicked = boolean;
}