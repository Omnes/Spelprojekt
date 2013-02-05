#include "Gameplay.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "WindowManager.h"

Gameplay::Gameplay() : 
	mLayerManager(), 
	mCamera(&mLayerManager)
{

}

Gameplay::~Gameplay(){

}

void Gameplay::update(){

	mLayerManager.update();
	mGui.update();
	mCamera.update();
}

void Gameplay::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mLayerManager.render();
	sf::View view = window->getView();
	window->setView(window->getDefaultView());
	mGui.render();
	window->setView(view);

}

States* Gameplay::createNew(){
	return new Gameplay;
}