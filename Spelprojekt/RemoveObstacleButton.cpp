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
	, mEmittAmount(emittAmount)
	, mSparksOnButton("Spark",100)
	, mSparksOnObstacles("Spark",1000){

		mSprite.setPosition(position);
		mSprite.setTexture(*mTexture);

		mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y)); //<--- texture rect

}

/*
 - Tror vi skulle tjäna endel på att göra en egen frametimer här istället för att använda sf::clock
		T.e.x så skulle det lösa att timern räknar när vi har pausat och att abilities är på cooldown när spelet startat
*/

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
				mCooldownTimer.restart();

			}else{
				i++;
			}
		}

		setClicked(false);
		
		mClickCooldownTimer.restart();
}



void RemoveObstacleButton::update(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	sf::Vector2f mousePosition = window->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

	mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	//om musen är över
	if(mSprite.getGlobalBounds().contains(mousePosition)){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*1,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		//om vi klickat över fyrkanten
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown){
			mGui->unclickAll();
			setClicked(true);
			mClickCooldownTimer.restart();
		}
	}

	//om vi klickat nånstans
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) 
		&& mClicked 
		&& mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown){

		if(mCooldownTimer.getElapsedTime().asSeconds() > mCooldown){

			killRelativePositionEntity(mousePosition);
		}else{
			mGui->unclickAll();
		}
	}

	if(mClicked){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*1,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		//mEmitter.setPosition(mSprite.getPosition());
		//mEmitter.burst(mSparksOnButton,sf::FloatRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y/mFrames),1);

		std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
		for(std::vector<Entity*>::iterator i = entityVector->begin();i != entityVector->end();i++){
			if(findID((*i)->getID())){
				sf::FloatRect rect = (*i)->getSprite()->getGlobalBounds();
				rect.left = -(*i)->getSprite()->getGlobalBounds().width/2 + (*i)->getPos().x;
				rect.top = -(*i)->getSprite()->getGlobalBounds().height/2 + (*i)->getPos().y;

				sf::FloatRect viewRect = sf::FloatRect(-window->getView().getSize().x/2 + window->getView().getCenter().x,-window->getView().getSize().y/2 + window->getView().getCenter().y,window->getView().getSize().x,window->getView().getSize().y);
				if(viewRect.intersects(rect)){
					mEmitter.setPosition(sf::Vector2f(0,0));
					mEmitter.burst(mSparksOnObstacles,rect,1);
				}
			}
		}

	}

	if(mCooldownTimer.getElapsedTime().asSeconds() < mCooldown){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*2,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	}
}


sf::Sprite* RemoveObstacleButton::getSprite(){

	return &mSprite;
}

void RemoveObstacleButton::setClicked(bool boolean){
	mClicked = boolean;
}