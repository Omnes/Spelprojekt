#include "Button.h"
#include "ResourceManager.h"
#include "EventManager.h"

Button::Button(sf::Vector2f pos, std::string evt, std::string img) : mPosition(pos), mEvent(evt), mImage(img){
	mSprite.setTexture(*(ResourceManager::getInst().getTexture(img)));
	mSprite.setPosition(mPosition);
}

Button::~Button(){

}


void Button::pressButton(sf::RenderWindow window){

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

		if(mSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){		
	
			EventManager::getInst().addEvent(mEvent);
		}
	}
}