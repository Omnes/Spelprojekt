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
#include "StartMeny.h"
#include "Gameplay.h"
#include "ResourceManager.h"

Game::Game(): mFrames(0), mCurrentFPS(0) {
	mClock.restart();
}

void Game::run(){

	srand(time(NULL));

	WindowManager* windowManager = &WindowManager::getInst();
	sf::RenderWindow* window = windowManager->getWindow();
	StateManager* stateManager = &StateManager::getInst();                                                      
	EventManager* eventManager = &EventManager::getInst();
	sf::Font FPSFont;
	FPSFont.getDefaultFont();

	//sf::Sprite aim = sf::Sprite(*ResourceManager::getInst().getTexture("Resources/Misc/pointer.png"));


	stateManager->addState(new StartMeny);

	while(window->isOpen()){

		sf::Text text;
		text.setFont(FPSFont);
		text.setColor(sf::Color::Green);
		text.setString(setStringStream(mCurrentFPS));
		text.setPosition(sf::Vector2f(100,100));

		sf::Event evt;
		while(window->pollEvent(evt)){
			if(evt.type == sf::Event::Closed){
				window->close();
			}
		}

		window->setView(window->getDefaultView());

		stateManager->update(); // main update
		countFrames();
		eventManager->update(); // process events
		
		window->clear(sf::Color::Black);
		
		stateManager->render(); //rendrering

		window->setView(window->getDefaultView());
		window->draw(text);

		//aim.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));

		//window->draw(aim);

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