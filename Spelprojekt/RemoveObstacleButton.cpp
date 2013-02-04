#include "RemoveObstacleButton.h"
#include "ResourceManager.h"
#include "LevelManager.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>

RemoveObstacleButton::RemoveObstacleButton(std::string obstacle,sf::Vector2f position, std::string texture)
	: mObstacle(obstacle)
	, mTexture(ResourceManager::getInst().getTexture(texture)){

		mSprite.setPosition(position);
		mSprite.setTexture(*mTexture);
		//vi ska ha en texrect här!

}

RemoveObstacleButton::~RemoveObstacleButton(){}

void RemoveObstacleButton::update(){
	sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition(*WindowManager::getInst().getWindow());

	if(mSprite.getGlobalBounds().contains(mousePosition)){
		//byt rekt
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			setClicked(true);
			//vi behöver nån timer här
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClicked){
		//loopa igenom entity vector
		//om getID() == mObstacle och getSprite()->getGlobalBounds->contains(mousePosition)
		//förstör hindret
	}
	//om mClicked byt rekt
}

sf::Sprite* RemoveObstacleButton::getSprite(){
	return &mSprite;
}

void RemoveObstacleButton::setClicked(bool boolean){
	mClicked = boolean;
}