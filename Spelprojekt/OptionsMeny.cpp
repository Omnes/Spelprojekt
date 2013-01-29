#include "OptionsMeny.h"
#include <SFML\Graphics\CircleShape.hpp>
#include "WindowManager.h"

OptionsMeny::OptionsMeny(){}

OptionsMeny::~OptionsMeny(){}

void OptionsMeny::update(){}

void OptionsMeny::render(){

	sf::CircleShape circle(10.0);
	circle.setFillColor(sf::Color::Blue);
	WindowManager::getInst().getWindow()->draw(circle);
}
