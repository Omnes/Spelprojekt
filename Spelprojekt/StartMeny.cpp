#include "StartMeny.h"
#include "WindowManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "StateManager.h"
#include "Animalipedia.h"
#include "OptionsMeny.h"
#include "EventManager.h"


#include <SFML\Window\Keyboard.hpp>

StartMeny::StartMeny(){

	mButtons.push_back(new Button(sf::Vector2f(1000,50), "addOptions","Resources/Menu/StartMenu/OptionsButton.png", "Resources/Sound/Menu/Menu_click.wav"));
	mButtons.push_back(new Button(sf::Vector2f(270,380), "startGameFirstTime","Resources/Menu/StartMenu/StartButton.png", "Resources/Sound/Menu/Menu_click.wav"));
	mButtons.push_back(new Button(sf::Vector2f(270,530), "exitGame","Resources/Menu/StartMenu/ExitButton.png", "Resources/Sound/Menu/Menu_click.wav"));

	mMusic = "Resources/Sound/Music/TitleScreen";
	mBackground.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/StartMenu/titlescreen.png"));




}

StartMeny::~StartMeny(){}

void StartMeny::update(){
	for (std::vector<Button*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->update();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		StateManager::getInst().addState(new OptionsMeny);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
		EventManager::getInst().addEvent("cutscene_1");
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
