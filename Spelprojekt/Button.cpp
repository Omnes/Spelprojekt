#include "Button.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"

Button::Button(sf::Vector2f pos, std::string evt, std::string img) : mPosition(pos), mEvent(evt), mImage(img){
	mSprite.setTexture(*(ResourceManager::getInst().getTexture(img)));
	mSprite.setPosition(mPosition);

}

Button::~Button(){

}


void Button::update(){

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		sf::RenderWindow* window = WindowManager::getInst().getWindow();
		if(mSprite.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))){		
	
			EventManager::getInst().addEvent(mEvent);
		}
	}
}

sf::Sprite& Button::getSprite(){

	return mSprite;
}