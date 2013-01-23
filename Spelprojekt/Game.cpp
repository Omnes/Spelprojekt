#include "Game.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "WindowManager.h"
#include <SFML\System\Clock.hpp>
#include "StateManager.h"
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\CircleShape.hpp>



float Game::elipsedTime = 0;

void Game::run(){

	
	WindowManager* windowManager = &WindowManager::getInst();
	sf::RenderWindow* window = windowManager->getWindow();
	StateManager* stateManager = &StateManager::getInst();

	sf::Clock clock;
	elipsedTime = clock.restart().asMilliseconds();

	stateManager->addState("gameplay");

	while(window->isOpen()){

		sf::Event evt;
		while(window->pollEvent(evt)){
			if(evt.type == sf::Event::Closed){
				window->close();
			}
		
		}
		

		elipsedTime += clock.restart().asMilliseconds();
		//while(elipsedTime > 1.0f/60){
			elipsedTime -= 1.0f/60;
			stateManager->update();
		//}
		
		window->clear();
		window->draw(sf::CircleShape(30));
		stateManager->render();
		window->display();
	
	}


}