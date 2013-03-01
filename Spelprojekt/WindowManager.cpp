#include "WindowManager.h"
#include "tinyxml2.h"
#include "ResourceManager.h"
#include <SFML\Window\Mouse.hpp>

WindowManager::WindowManager(){
	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/data/settings.xml");

	std::string title = doc.FirstChildElement("Window")->FirstChildElement("Title")->GetText();

	const tinyxml2::XMLAttribute* res = doc.FirstChildElement("Window")->FirstChildElement("Resolution")->FirstAttribute();

	float width = res->IntValue();
	float heigth = res->Next()->IntValue();

	bool fullscreen = res->Next()->Next()->BoolValue();
	
	mWindow = new sf::RenderWindow(sf::VideoMode(width,heigth),title,fullscreen ? sf::Style::Fullscreen : sf::Style::Close);

	const tinyxml2::XMLAttribute* attr = doc.FirstChildElement("Window")->FirstAttribute();

	int frameLimit = attr->IntValue();
	attr = attr->Next();
	bool vsync = attr->BoolValue();
	mWindow->setVerticalSyncEnabled(vsync);
	mWindow->setFramerateLimit(frameLimit);

	
	mDefaultView = new sf::View(mWindow->getDefaultView());
	float zoomfactor = 1280 / width;

	mDefaultView->zoom(zoomfactor);

	mAim = sf::Sprite(*ResourceManager::getInst().getTexture("Resources/Misc/cursor.png"));
	mAim.setOrigin(mAim.getTexture()->getSize().x/4, mAim.getTexture()->getSize().y/2);
	mAim.setTextureRect(sf::IntRect(0,0,mAim.getTexture()->getSize().x/2, mAim.getTexture()->getSize().y));

	//mDefaultView->rotate(180);

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