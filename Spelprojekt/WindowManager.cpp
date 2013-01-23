#include "WindowManager.h"

WindowManager::WindowManager(){
	mWindow = new sf::RenderWindow(sf::VideoMode(800,600),"Flykten",sf::Style::Default);
}

WindowManager::~WindowManager(){


}

WindowManager& WindowManager::getInst(){

	static WindowManager instance;
	return instance;
}

sf::RenderWindow* WindowManager::getWindow(){

	return mWindow;
}

