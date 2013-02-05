#include "Gui.h"
#include "ResourceManager.h"
#include "RemoveObstacleButton.h"
#include "WindowManager.h"

Gui::Gui(): mWindow(WindowManager::getInst().getWindow()){
	mButtons.push_back(new RemoveObstacleButton("Stone",sf::Vector2f(0,100),"knapp1.jpg",this));
	mButtons.push_back(new RemoveObstacleButton("Gren",sf::Vector2f(0,250),"knapp2.jpg",this));
}

void Gui::update(){
	for(AbilityButtons::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->update();
	}
}

void Gui::render(){
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