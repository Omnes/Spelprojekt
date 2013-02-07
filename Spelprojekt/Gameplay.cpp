#include "Gameplay.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "WindowManager.h"
#include "EventManager.h"

Gameplay::Gameplay(){
	mLayerManager = new LayerManager;
	mCamera = new Camera(mLayerManager);

}

Gameplay::~Gameplay(){
	delete mCamera;
	delete mLayerManager;
	WindowManager::getInst().getWindow()->setView(WindowManager::getInst().getWindow()->getDefaultView());
}

void Gameplay::update(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->setView(*mCamera->getView());

	mLayerManager->update();
	mGui.update();
	mCamera->update();

	window->setView(window->getDefaultView());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		EventManager::getInst().addEvent("addPause");
	}
}

void Gameplay::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->setView(*mCamera->getView());
	mLayerManager->render();
	window->setView(window->getDefaultView());
	mGui.render();
	
	

}
