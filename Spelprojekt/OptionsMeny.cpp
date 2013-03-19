#include "OptionsMeny.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "ResourceManager.h"

OptionsMeny::OptionsMeny()
	: mApplyButton(sf::Vector2f(900,600),"Resources/Menu/knapp.png","Resources/Sound/Menu/Menu_forward.wav",this){
	mCheckboxes.push_back(new Checkbox(sf::Vector2f(850,165),"Resolution","fullscreen"));
	mCheckboxes.push_back(new Checkbox(sf::Vector2f(270,435),"Sound","muted"));
	mCheckboxes.push_back(new Checkbox(sf::Vector2f(850,215),"Tutorial","play"));


	//�ndra till vector sen.
	mOptionSliders.push_back(new OptionSlider(sf::Vector2f(50,140), "Sound", "musicVolume"));
	mOptionSliders.push_back(new OptionSlider(sf::Vector2f(50,240), "Sound", "soundVolume"));
	mOptionSliders.push_back(new OptionSlider(sf::Vector2f(50,340), "Sound", "voiceVolume"));

	mMusic = "Resources/Sound/Music/Title_Screen_";


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

	//vector med sliders
	for(OptionSliders::iterator i = mOptionSliders.begin(); i != mOptionSliders.end(); i++){
		(*i)->update();
	}

}

void OptionsMeny::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->draw(mBackground);

	for (std::vector<Checkbox*>::iterator i = mCheckboxes.begin(); i != mCheckboxes.end(); i++){
		(*i)->render(); 
	}
	window->draw(mApplyButton.getSprite());

	//vector med sliders
	for(OptionSliders::iterator i = mOptionSliders.begin(); i != mOptionSliders.end(); i++){
		(*i)->render();
	}

}

std::string OptionsMeny::getMusic(){
	return mMusic;
}

void OptionsMeny::saveSettings(){

	for(std::vector<Checkbox*>::iterator i = mCheckboxes.begin(); i != mCheckboxes.end();i++){
		(*i)->saveSetting();
	}

	//g�r om till vector
	for(OptionSliders::iterator i = mOptionSliders.begin(); i != mOptionSliders.end(); i++){
		(*i)->saveSettings();
	}

	EventManager::getInst().addEvent("goBackToStartFromOptions");


}
