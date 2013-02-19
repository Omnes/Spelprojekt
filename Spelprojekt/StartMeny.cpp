#include "StartMeny.h"
#include "WindowManager.h"
#include "SoundManager.h"
StartMeny::StartMeny(){

	mButtons.push_back(new Button(sf::Vector2f(100,100), "addGameplay","Resources/Misc/knapp1.jpg", "Resources/Sound/test.wav"));
	mButtons.push_back(new Button(sf::Vector2f(100,300), "addTaktik","Resources/Misc/knapp2.jpg","Resources/Sound/test.wav"));
	mButtons.push_back(new Button(sf::Vector2f(100,500), "addMap","Resources/Misc/knapp3.jpg","Resources/Sound/test.wav"));
	mMusic = "Resources/Sound/TitleScreen";
}

StartMeny::~StartMeny(){}

void StartMeny::update(){
	for (std::vector<Button*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->update();
	}
}

void StartMeny::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	for (std::vector<Button*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		window->draw((*i)->getSprite());
	}
}

std::string StartMeny::getMusic(){
	return mMusic;
}
