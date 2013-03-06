#include "OptionsMeny.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "ResourceManager.h"

OptionsMeny::OptionsMeny()
	: mApplyButton(sf::Vector2f(900,600),"Resources/Menu/knapp.png","",this){
	mCheckboxes.push_back(new Checkbox(sf::Vector2f(1050,165),"Resolution","fullscreen"));
	mCheckboxes.push_back(new Checkbox(sf::Vector2f(270,435),"Sound","muted"));
	mMusic = "Resources/Sound/TitleScreen";


	mBackground.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/OptionsMenu/OptionsBG.png"));
}

OptionsMeny::~OptionsMeny(){
	while(!mCheckboxes.empty()){
		delete mCheckboxes.back();
		mCheckboxes.pop_back();
	}
}

void OptionsMeny::update(){
	for (std::vector<Checkbox*>::iterator i = mCheckboxes.begin(); i != mCheckboxes.end(); i++){
		(*i)->update();
	}
	mApplyButton.update();
}

void OptionsMeny::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->draw(mBackground);

	for (std::vector<Checkbox*>::iterator i = mCheckboxes.begin(); i != mCheckboxes.end(); i++){
		(*i)->render(); 
	}
	window->draw(mApplyButton.getSprite());
}

std::string OptionsMeny::getMusic(){
	return mMusic;
}

void OptionsMeny::saveSettings(){

	for(std::vector<Checkbox*>::iterator i = mCheckboxes.begin(); i != mCheckboxes.end();i++){
		(*i)->saveSetting();
	}

	EventManager::getInst().addEvent("goBackToStartFromOptions");


}
