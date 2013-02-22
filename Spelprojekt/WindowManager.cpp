#include "WindowManager.h"

WindowManager::WindowManager(){
	mWindow = new sf::RenderWindow(sf::VideoMode(1280,720),"Flykten",sf::Style::Close);
	mWindow->setVerticalSyncEnabled(true);
	mWindow->setFramerateLimit(60);

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

