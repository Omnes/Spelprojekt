#include "StartMeny.h"
#include "WindowManager.h"
StartMeny::StartMeny(){
	mButtons.push_back(new Button(sf::Vector2f(100,100), "exitGame","knapp1.jpg"));
	mButtons.push_back(new Button(sf::Vector2f(100,200), "addMap","knapp2.jpg"));
	mButtons.push_back(new Button(sf::Vector2f(100,300), "addOptions","knapp3.jpg"));
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

