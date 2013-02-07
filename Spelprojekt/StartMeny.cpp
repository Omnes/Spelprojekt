#include "StartMeny.h"
#include "WindowManager.h"
StartMeny::StartMeny(){

	mButtons.push_back(new Button(sf::Vector2f(100,100), "addGameplay","knapp1.jpg", "Resources/Sound/test.wav"));
	mButtons.push_back(new Button(sf::Vector2f(100,300), "addTaktik","knapp2.jpg","Resources/Sound/test.wav"));
	mButtons.push_back(new Button(sf::Vector2f(100,500), "addMap","knapp3.jpg","Resources/Sound/test.wav"));

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
