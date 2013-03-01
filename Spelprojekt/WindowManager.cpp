#include "WindowManager.h"
#include "tinyxml2.h"
#include "ResourceManager.h"
#include <SFML\Window\Mouse.hpp>

WindowManager::WindowManager(){

	mWindow = 0;

	createWindow();

	mAim = sf::Sprite(*ResourceManager::getInst().getTexture("Resources/Misc/cursor.png"));
	mAim.setScale(sf::Vector2f(0.5,0.5));
	mAim.setOrigin(mAim.getTexture()->getSize().x/(8*2), mAim.getTexture()->getSize().y/8);
	mAim.setTextureRect(sf::IntRect(0,0,mAim.getTexture()->getSize().x/2, mAim.getTexture()->getSize().y));

}

void WindowManager::createWindow(){

	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/data/settings.xml");

	std::string title = doc.FirstChildElement("Window")->FirstChildElement("Title")->GetText();

	tinyxml2::XMLElement* res = doc.FirstChildElement("Resolution");

	float width = res->FloatAttribute("width");
	float heigth = res->FloatAttribute("heigth");

	bool fullscreen = res->BoolAttribute("fullscreen");

	if(mWindow != 0){
		delete mWindow;
	}
	
	mWindow = new sf::RenderWindow(sf::VideoMode(width,heigth),title,fullscreen ? sf::Style::Fullscreen : sf::Style::Close);

	tinyxml2::XMLElement* win = doc.FirstChildElement("Window");

	int frameLimit = win->IntAttribute("framelimit");
	bool vsync = win->BoolAttribute("vsync");
	mWindow->setVerticalSyncEnabled(vsync);
	mWindow->setFramerateLimit(frameLimit);

	
	mDefaultView = new sf::View(mWindow->getDefaultView());
	float zoomfactor = 1280 / width;

	mDefaultView->zoom(zoomfactor);

	//mDefaultView->setCenter(mDefaultView->getSize().x/2,mDefaultView->getSize().y/2);
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

sf::View* WindowManager::getDefaultView(){
	return mDefaultView;
}

sf::Sprite* WindowManager::getCursor(){

	return &mAim;
}
