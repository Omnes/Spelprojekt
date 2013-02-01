#include "Game.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "WindowManager.h"
#include <SFML\System\Clock.hpp>
#include "StateManager.h"
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include "EventManager.h"
#include <time.h>


void Game::run(){

	srand(time(NULL));

	WindowManager* windowManager = &WindowManager::getInst();
	sf::RenderWindow* window = windowManager->getWindow();
	StateManager* stateManager = &StateManager::getInst();
	EventManager* eventManager = &EventManager::getInst();

	stateManager->addState("gameplay");


	while(window->isOpen()){

		sf::Event evt;
		while(window->pollEvent(evt)){
			if(evt.type == sf::Event::Closed){
				window->close();
			}
		}

		stateManager->update(); // main update

		eventManager->update(); // process events
		
		window->clear(sf::Color::Black);
		stateManager->render(); //rendrering
		window->display();
	
	}


}