#pragma once
#include "Particle.h"
#include "Behavior.h"
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class AvoidMouse : public Behavior{
private:
	sf::RenderWindow& window;

public:

	AvoidMouse(sf::RenderWindow& win): window(win){}

	/*virtual*/ void update(Particle* particle){
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f dir = particle->mPosition - sf::Vector2f(mousePos.x,mousePos.y);
		particle->mDirection = dir*(1.0f/(std::sqrtf(dir.x*dir.x + dir.y*dir.y)));
		
	}

	/*virtual*/ ~AvoidMouse(){};

};