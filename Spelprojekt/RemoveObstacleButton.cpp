#include "RemoveObstacleButton.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "ActiveLayer.h"
#include "Entity.h"
#include "Gui.h"
#include <SFML\Graphics\CircleShape.hpp>
#include "SoundManager.h"

RemoveObstacleButton::RemoveObstacleButton(std::vector<std::string> obstacle,sf::Vector2f position, std::string texture,float cooldown, std::string particleName, int emittAmount, std::string soundFX, Gui* gui)
	: mObstacles(obstacle)
	, mTexture(ResourceManager::getInst().getTexture(texture))
	, mFrames(3)
	, mCooldown(cooldown)
	, mClickCooldown(75)
	, mGui(gui)
	, mClicked(false)
	, mParticleSystem(particleName,100)
	, mEmittAmount(emittAmount)
	, mSparksOnObstacles("Spark",600)
	, mMissedAbility("Smoke",300)
	, mWrongAbility("Kryss",3)
	, mSoundFX(*ResourceManager::getInst().getSoundBuffer(soundFX))
	, mSoundWrong(*ResourceManager::getInst().getSoundBuffer("Resources/Sound/Effekts/Strength_effekt.wav")){

		mSprite.setPosition(position);
		mSprite.setTexture(*mTexture);

		mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y)); //<--- texture rect

}

/*
 - Tror vi skulle tj�na endel p� att g�ra en egen frametimer h�r ist�llet f�r att anv�nda sf::clock
		T.e.x s� skulle det l�sa att timern r�knar n�r vi har pausat och att abilities �r p� cooldown n�r spelet startat
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
		//hitta vad vi har musen �ver och d�da den
		bool didDelete = false;
		bool didHit = false;
		for(std::vector<Entity*>::iterator i = entityVector->begin();i != entityVector->end();){
			sf::FloatRect bounds = (*i)->getSprite()->getGlobalBounds();
			bool contains = bounds.contains(relativeMousePosition);

			sf::FloatRect rect = (*i)->getSprite()->getGlobalBounds();
			rect.left = -(*i)->getSprite()->getGlobalBounds().width/2 + (*i)->getPos().x;
			rect.top = -(*i)->getSprite()->getGlobalBounds().height/2 + (*i)->getPos().y;
			 
			std::string id = (*i)->getID();

			if(contains){
				if(findID(id)){
					mEmitter.setPosition(sf::Vector2f(0,0));
					mEmitter.burst(mParticleSystem,rect,mEmittAmount);
					delete *i;
					i = entityVector->erase(i);
					mCooldownTimer.restart();
					didDelete = true;
					SoundManager::getInst().play(mSoundFX);
					setClicked(false);
				}
				else{
					i++;
					if(id != "Animal" && id != "Fire"){
						if(mCooldownSound.getElapsedTime().asSeconds() > 1){
							mEmitter.setPosition(relativeMousePosition);
							mEmitter.burst(mWrongAbility, 1);
							SoundManager::getInst().play(mSoundWrong);
							mCooldownSound.restart();
						}
						didHit = true;
					}
				}
			}
			else{
				i++;
			}
		}

		if(!didDelete && !didHit){
			mEmitter.setPosition(relativeMousePosition);
			mEmitter.burst(mMissedAbility,10,1);
		}

		//setClicked(false);
		
		mClickCooldownTimer.restart();
}



void RemoveObstacleButton::update(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	sf::Vector2f mousePosition = window->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

	mSprite.setTextureRect(sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
	//om musen �r �ver
	if(mSprite.getGlobalBounds().contains(mousePosition)){
		mSprite.setTextureRect(sf::IntRect(mTexture->getSize().x/mFrames*1,0,mTexture->getSize().x/mFrames,mTexture->getSize().y));
		//om vi klickat �ver fyrkanten
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown && mCooldownTimer.getElapsedTime().asSeconds() > mCooldown){
			mGui->unclickAll();
			setClicked(true);
			mClickCooldownTimer.restart();
		}
	}

	//om vi klickat n�nstans
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
					mEmitter.burst(mSparksOnObstacles,rect,2);
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
	WindowManager::getInst().getCursor()->setTextureRect(sf::IntRect(WindowManager::getInst().getCursor()->getTexture()->getSize().x/2*boolean,0,WindowManager::getInst().getCursor()->getTexture()->getSize().x/2,WindowManager::getInst().getCursor()->getTexture()->getSize().y));

}