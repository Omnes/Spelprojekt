#include "RemoveObstacleButton.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "ActiveLayer.h"
#include "Entity.h"
#include "Gui.h"
#include <SFML\Graphics\CircleShape.hpp>

RemoveObstacleButton::RemoveObstacleButton(std::string obstacle,sf::Vector2f position, std::string texture, Gui* gui)
	: mObstacle(obstacle)
	, mTexture(ResourceManager::getInst().getTexture(texture))
	, mFrames(4)
	, mCooldown(100)
	, mClickCooldown(75)
	, mGui(gui)
	, mClicked(false){

		mSprite.setPosition(position);
		mSprite.setTexture(*mTexture);

		mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y)); //<--- texture rect

}

RemoveObstacleButton::~RemoveObstacleButton(){}


void RemoveObstacleButton::killRelativePositionEntity(sf::Vector2f mousePosition){
	const sf::View* view = &WindowManager::getInst().getWindow()->getView();
	sf::Vector2f relativeMousePosition = mousePosition + view->getCenter() - sf::Vector2f(view->getSize().x/2,view->getSize().y/2);

		std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
		//hitta vad vi har musen över och döda den
		for(std::vector<Entity*>::iterator i = entityVector->begin();i != entityVector->end();){
			sf::FloatRect bounds = (*i)->getSprite()->getGlobalBounds();
			bool contains = bounds.contains(relativeMousePosition);
			if((*i)->getID() == mObstacle && contains){
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

	sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition(*WindowManager::getInst().getWindow());

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
		&& mCooldownTimer.getElapsedTime().asMilliseconds() > mCooldown){

		killRelativePositionEntity(mousePosition);
	}

	

	if(mCooldownTimer.getElapsedTime().asMilliseconds() < mCooldown){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*3,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}

	if(mClicked){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*2,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}
}

sf::Sprite* RemoveObstacleButton::getSprite(){

	sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition(*WindowManager::getInst().getWindow());

	//KORTA NER DEN
	const sf::View* view = &WindowManager::getInst().getWindow()->getView();
	sf::Vector2f relativeMousePosition = mousePosition + view->getCenter() - sf::Vector2f(view->getSize().x/2,view->getSize().y/2);
	sf::CircleShape mousecircle(10);
	mousecircle.setOrigin(5,5);
	mousecircle.setPosition(relativeMousePosition);
	WindowManager::getInst().getWindow()->draw(mousecircle);

	return &mSprite;
}

void RemoveObstacleButton::setClicked(bool boolean){
	mClicked = boolean;
}