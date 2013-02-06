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

	mLayerManager->update();
	mGui.update();
	mCamera->update();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		EventManager::getInst().addEvent("addPause");
	}
}

void Gameplay::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mLayerManager->render();
	sf::View view = window->getView();
	window->setView(window->getDefaultView());
	mGui.render();
	window->setView(view);

}
