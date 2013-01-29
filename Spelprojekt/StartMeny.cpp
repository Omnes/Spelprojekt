#include "StartMeny.h"
#include "WindowManager.h"
StartMeny::StartMeny(){
	mButtons.push_back(new Button(sf::Vector2f(100,100), "exitGame","knapp1.jpg"));
	/*mButtons.push_back(new Button(sf::Vector2f(100,200), "event2","knapp2.png"));
	mButtons.push_back(new Button(sf::Vector2f(100,300), "event3","knapp3.png"));*/
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

