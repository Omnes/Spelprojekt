#include "Gameplay.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "WindowManager.h"
#include "ParticleManager.h"
#include "EventManager.h"
#include "LevelManager.h"

Gameplay::Gameplay(){
	mLayerManager = new LayerManager;
	mCamera = new Camera(mLayerManager);

	mMusic = LevelManager::getInst().getMusicOnLevel();

}

Gameplay::~Gameplay(){
	delete mCamera;
	delete mLayerManager;
	WindowManager::getInst().getWindow()->setView(WindowManager::getInst().getWindow()->getDefaultView());
}

void Gameplay::update(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	ParticleManager* particleManager = &ParticleManager::getInst();

	window->setView(*mCamera->getView());

	mLayerManager->update();
	particleManager->update();
	mGui.update();
	mCamera->update();

	window->setView(window->getDefaultView());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		EventManager::getInst().addEvent("addPause");
	}
}

void Gameplay::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	ParticleManager* particleManager = &ParticleManager::getInst();

	window->setView(*mCamera->getView());
	mLayerManager->render();
	particleManager->render(*window);
	window->setView(window->getDefaultView());
	mGui.render();
	
	

}

void Gameplay::renderFromTacVision(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	ParticleManager* particleManager = &ParticleManager::getInst();

	mLayerManager->render();
	particleManager->render(*window);
	window->setView(window->getDefaultView());
	mGui.render();

}

LayerManager* Gameplay::getLayerManager(){

	return mLayerManager;
}

std::string Gameplay::getMusic(){
	return mMusic;
}