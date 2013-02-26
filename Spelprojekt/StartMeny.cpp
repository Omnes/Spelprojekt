#include "StartMeny.h"
#include "WindowManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "StateManager.h"
#include "Animalipedia.h"

#include <SFML\Window\Keyboard.hpp>

StartMeny::StartMeny(){

	mButtons.push_back(new Button(sf::Vector2f(800,200), "addMap","Resources/Menu/StartButton.png", "Resources/Sound/test.wav"));
	mButtons.push_back(new Button(sf::Vector2f(800,400), "exitGame","Resources/Menu/ExitGameButton.png","Resources/Sound/test.wav"));
	mMusic = "Resources/Sound/TitleScreen";
	mBackground.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/startMeny.png"));
}

StartMeny::~StartMeny(){}

void StartMeny::update(){
	for (std::vector<Button*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->update();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		StateManager::getInst().addState(new Animalipedia);
	}
}

void StartMeny::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->draw(mBackground);

	for (std::vector<Button*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		window->draw((*i)->getSprite());
	}
}

std::string StartMeny::getMusic(){
	return mMusic;
}
