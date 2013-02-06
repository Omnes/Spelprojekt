#include "OptionsMeny.h"
#include "WindowManager.h"
OptionsMeny::OptionsMeny(){
	mButtons.push_back(new Button(sf::Vector2f(100,100), "addStart","knapp1.jpg"));
}

OptionsMeny::~OptionsMeny(){}

void OptionsMeny::update(){
	for (std::vector<Button*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->update();
	}
}

void OptionsMeny::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	for (std::vector<Button*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		window->draw((*i)->getSprite());
	}
}
