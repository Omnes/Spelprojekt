#include "Gameplay.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include "WindowManager.h"
#include "ParticleManager.h"
#include "EventManager.h"
#include "LevelManager.h"
#include "StateManager.h"
#include "Countdown.h"

Gameplay::Gameplay(){
	mLayerManager = new LayerManager;
	mCamera = new Camera(mLayerManager);

	mMusic = LevelManager::getInst().getMusicOnLevel();
	update();
	
}

Gameplay::~Gameplay(){
	delete mCamera;
	delete mLayerManager;
	WindowManager::getInst().getWindow()->setView(*WindowManager::getInst().getDefaultView());
}

void Gameplay::update(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	ParticleManager* particleManager = &ParticleManager::getInst();

	window->setView(*mCamera->getView());

	mLayerManager->update();
	particleManager->update();
	mGui.update();
	mCamera->update();

	window->setView(*WindowManager::getInst().getDefaultView());

}

void Gameplay::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	ParticleManager* particleManager = &ParticleManager::getInst();

	window->setView(*mCamera->getView());
	mLayerManager->render();
	particleManager->render(*window);
	window->setView(*WindowManager::getInst().getDefaultView());
	mGui.render();
	
	

}

void Gameplay::renderFromTacVision(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	ParticleManager* particleManager = &ParticleManager::getInst();

	mLayerManager->render();
	particleManager->render(*window);
	window->setView(*WindowManager::getInst().getDefaultView());
	mGui.render();

}

LayerManager* Gameplay::getLayerManager(){

	return mLayerManager;
}

std::string Gameplay::getMusic(){
	return mMusic;
}