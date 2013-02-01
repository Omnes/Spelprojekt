#include "Game.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "WindowManager.h"
#include <SFML\System\Clock.hpp>
#include "StateManager.h"
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include "EventManager.h"
#include <time.h>
#include <sstream>

Game::Game(): mFrames(0), mCurrentFPS(0) {
	mClock.restart();
}

void Game::run(){

	srand(time(NULL));

	WindowManager* windowManager = &WindowManager::getInst();
	sf::RenderWindow* window = windowManager->getWindow();
	StateManager* stateManager = &StateManager::getInst();                                                      
	EventManager* eventManager = &EventManager::getInst();

	stateManager->addState("gameplay");


	while(window->isOpen()){

		sf::Text text;
		text.setString(setStringStream(mCurrentFPS));
		sf::Event evt;
		while(window->pollEvent(evt)){
			if(evt.type == sf::Event::Closed){
				window->close();
			}
		}

		stateManager->update(); // main update
		countFrames();
		eventManager->update(); // process events
		
		window->clear(sf::Color::Black);
		stateManager->render(); //rendrering
		window->draw(text);
		window->display();
	
	}


}

void Game::countFrames(){

	mFrames++;
	if(mClock.getElapsedTime().asSeconds()>1){
		mCurrentFPS=mFrames;
		mFrames=0;
		mClock.restart();

	}
}

std::string Game::setStringStream(int frames){

	std::stringstream ss; 
	ss << frames; 
	return ss.str();

}