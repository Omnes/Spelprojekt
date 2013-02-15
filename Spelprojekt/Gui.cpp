#include "Gui.h"
#include "ResourceManager.h"
#include "RemoveObstacleButton.h"
#include "WindowManager.h"
#include "TacticalVisionButton.h"
<<<<<<< HEAD
#include "InnerBeastButton.h"

Gui::Gui(): mWindow(WindowManager::getInst().getWindow()){
	mButtons.push_back(new RemoveObstacleButton("Stone",sf::Vector2f(0,100),"Resources/Misc/knapp1.jpg",this));
	mButtons.push_back(new RemoveObstacleButton("Gren",sf::Vector2f(0,250),"Resources/Misc/knapp2.jpg",this));
	mButtons.push_back(new TacticalVisionButton(sf::Vector2f(0,400),"Resources/Misc/knapp1.jpg",this));
	mButtons.push_back(new InnerBeastButton(sf::Vector2f(0,600),"Resources/Misc/knapp2.jpg",this));
=======
#include <string>

Gui::Gui(): mWindow(WindowManager::getInst().getWindow()){

	std::vector<std::string> button1vector;
	button1vector.push_back("Stone");
	button1vector.push_back("FallenTree");

	std::vector<std::string> button2vector;
	button2vector.push_back("Bees");
	button2vector.push_back("GarbageSwamp");
	button2vector.push_back("Box");
	button2vector.push_back("Oil");

	mButtons.push_back(new RemoveObstacleButton(button1vector,sf::Vector2f(0,100),"Resources/GUI/elephantcrush.png",this));
	mButtons.push_back(new RemoveObstacleButton(button2vector,sf::Vector2f(0,250),"Resources/GUI/diskmedel.png",this));
	mButtons.push_back(new TacticalVisionButton(sf::Vector2f(0,400),"Resources/GUI/sonar.png",this));
>>>>>>> b9d789ac26e978240cce581abb7785baf69f990e
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