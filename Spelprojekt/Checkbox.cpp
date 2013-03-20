#include "Checkbox.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "tinyxml2.h"

Checkbox::Checkbox(sf::Vector2f position,std::string element,std::string attribute)
	: mTex(ResourceManager::getInst().getTexture("Resources/Menu/OptionsMenu/checkbox3.png"))
	, mSprite(*mTex)
	, mElement(element)
	, mAttribute(attribute)
	, mClickCooldown(200)
	, mCurrentImage(0)
	, mFrames(4){

		mSprite.setPosition(position);
		mSprite.setTextureRect(sf::IntRect(0,0,mTex->getSize().x/mFrames,mTex->getSize().y));


	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/Settings.xml");

	mChecked = doc.FirstChildElement(mElement.c_str())->BoolAttribute(mAttribute.c_str());

}

Checkbox::~Checkbox(){
	
}

void Checkbox::update(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());
	
	if(mSprite.getGlobalBounds().contains(mousePosition)){		
	
		mCurrentImage = 1 + mChecked*2;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClickCooldownTimer.getElapsedTime().asMilliseconds() > mClickCooldown){ 
			mClickCooldownTimer.restart();
			mChecked = !mChecked;
			saveSetting();
		}		
	}

	else{

		mCurrentImage = 0 + mChecked*2;
	}


	float left = mTex->getSize().x/mFrames * mCurrentImage;
	mSprite.setTextureRect(sf::IntRect(left,0,mTex->getSize().x/mFrames,mTex->getSize().y));

}

void Checkbox::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	window->draw(mSprite);
}

void Checkbox::saveSetting(){

	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/settings.xml");

	doc.FirstChildElement(mElement.c_str())->SetAttribute(mAttribute.c_str(),mChecked);

	doc.SaveFile("Resources/Data/settings.xml");

}