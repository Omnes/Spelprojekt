#include "Game.h"

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Window\Event.hpp>

#include <time.h>
#include <sstream>

#include "WindowManager.h"
#include "StateManager.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "ParticleManager.h"
#include "SoundManager.h"
#include "FontMaster.h"

#include "StartMeny.h"
#include "ScrollDetector.h"




Game::Game(): mFrames(0), mCurrentFPS(0) {
	mClock.restart();
	mInFocus = true;
}

void Game::run(){
	
	srand(time(NULL));

	WindowManager* windowManager = &WindowManager::getInst();
	sf::RenderWindow* window = windowManager->getWindow();
	StateManager* stateManager = &StateManager::getInst();                                                      
	EventManager* eventManager = &EventManager::getInst();
	SoundManager* soundManager = &SoundManager::getInst();
	ParticleManager* particleManager = &ParticleManager::getInst();
	particleManager->loadAllParticlesFromFile("Resources/data/Particle/ParticleList.xml");
	FontMaster::loadFonts();

	stateManager->addState(new StartMeny);

	while(window->isOpen()){

		
		PollWindowEvents(window);
		
		if(mInFocus){

			window->setView(*windowManager->getDefaultView());

			eventManager->update(); // process events
			window = windowManager->getWindow(); // <--- krashar i options meny om vi inte har den h�r eftersom vi skapar ett nytt f�nster under StateManager->update();

			stateManager->update(); // main update
			
			soundManager->update();

			countFrames();
			
		
			window->clear(sf::Color::Black);
		
			stateManager->render(); //rendrering
			//particleManager->render(*window); // denna ska nog ligga i varje states update (tex i activeLayer vid r�tt lager)

			window->setView(*windowManager->getDefaultView());
			//drawFPS(window);

			//window->setMouseCursorVisible(false);
			
			WindowManager::getInst().getCursor()->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
			window->draw(*WindowManager::getInst().getCursor());

			window->display();
		}
	
	}


}

void Game::drawFPS(sf::RenderWindow* window){
	sf::Text text;
	text.setColor(sf::Color::Green);
	text.setString(setStringStream(mCurrentFPS));
	text.setPosition(sf::Vector2f(0,0));
	window->draw(text);
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

void Game::PollWindowEvents(sf::RenderWindow* window){

	sf::Event evt;
	while(window->pollEvent(evt)){

		if(evt.type == sf::Event::Closed){
			window->close();
		}
		if(evt.type == sf::Event::LostFocus){
			mInFocus = false;
		}
		if(evt.type == sf::Event::GainedFocus){
			mInFocus = true;
		}
		ScrollDetector::setScrollDelta(0);
		if(evt.type == sf::Event::MouseWheelMoved){
			ScrollDetector::setScrollDelta(evt.mouseWheel.delta);
		}
	}
}