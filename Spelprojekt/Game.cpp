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

#include "StartMeny.h"




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
	ParticleManager* particleManager = &ParticleManager::getInst();
	particleManager->loadPrototype("Resources/Particle/buttonParticle.xml"); // <------- ska bort härifrån annars ser det ut som zumas kod
	particleManager->loadPrototype("Resources/Particle/firewallParticle.xml");
	particleManager->loadPrototype("Resources/Particle/smokeParticle.xml");

	//sf::Sprite aim = sf::Sprite(*ResourceManager::getInst().getTexture("Resources/Misc/pointer.png"));


	stateManager->addState(new StartMeny);

	while(window->isOpen()){

		
		PollWindowEvents(window);
		
		if(mInFocus){

			window->setView(window->getDefaultView());

			stateManager->update(); // main update

			countFrames();
			eventManager->update(); // process events
		
			window->clear(sf::Color::Black);
		
			stateManager->render(); //rendrering
			//particleManager->render(*window); // denna ska nog ligga i varje states update (tex i activeLayer vid rätt lager)

			window->setView(window->getDefaultView());
			drawFPS(window);

			//aim.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));

			//window->draw(aim);

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
	}
}