#include "FakeAbilityButton.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include <SFML\Window\Mouse.hpp>

FakeAbilityButton::FakeAbilityButton(sf::Vector2f position, std::string buttontexture, std::string obstaclestexture) : mPosition(position), mButtonActivated(false){
	mSpriteButton = new sf::Sprite;
	mSpriteInfo = new sf::Sprite;
	sf::Texture* tex = ResourceManager::getInst().getTexture(buttontexture);
	mSpriteButton->setTexture(*tex);
	mSpriteButton->setTextureRect(sf::IntRect(0,0,tex->getSize().x/3,tex->getSize().y));
	mSpriteButton->setPosition(mPosition);
	mSpriteInfo->setTexture(*ResourceManager::getInst().getTexture(obstaclestexture));
	mSpriteInfo->setPosition(mPosition.x, mPosition.y - 100);

}
	
FakeAbilityButton::~FakeAbilityButton(){
	delete mSpriteButton;
	delete mSpriteInfo;

}

void FakeAbilityButton::update(){

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());
	
	if(mSpriteButton->getGlobalBounds().contains(mousePosition)){

		mSpriteButton->setTextureRect(sf::IntRect(mSpriteButton->getTexture()->getSize().x/3,0,mSpriteButton->getTexture()->getSize().x/3,mSpriteButton->getTexture()->getSize().y));
		mButtonActivated = true;
	}

	else{
	
		mSpriteButton->setTextureRect(sf::IntRect(0,0,mSpriteButton->getTexture()->getSize().x/3,mSpriteButton->getTexture()->getSize().y));
		mButtonActivated = false;
	}

}

void FakeAbilityButton::render(){

	sf::RenderWindow *window = WindowManager::getInst().getWindow();	
	
	window->draw(*mSpriteButton);

	if(mButtonActivated){

		window->draw(*mSpriteInfo);
	}
}

	

