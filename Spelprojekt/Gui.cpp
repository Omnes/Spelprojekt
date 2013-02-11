#include "Gui.h"
#include "ResourceManager.h"
#include "RemoveObstacleButton.h"
#include "WindowManager.h"
#include "TacticalVisionButton.h"

Gui::Gui(): mWindow(WindowManager::getInst().getWindow()){
	mButtons.push_back(new RemoveObstacleButton("Stone",sf::Vector2f(0,100),"knapp1.jpg",this));
	mButtons.push_back(new RemoveObstacleButton("Gren",sf::Vector2f(0,250),"knapp2.jpg",this));
	mButtons.push_back(new TacticalVisionButton(sf::Vector2f(0,400),"knapp1.jpg",this));
	mGuiSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Misc/Ui.png"));
	mGuiSprite.setPosition(sf::Vector2f(0,720-72));
}

void Gui::update(){
	for(AbilityButtons::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->update();
	}
}

void Gui::render(){
	mWindow->draw(mGuiSprite);
	for(AbilityButtons::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		mWindow->draw(*(*i)->getSprite());
	}
}

void Gui::unclickAll(){
	for(AbilityButtons::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->setClicked(false);
	}
}

Gui::~Gui(){}