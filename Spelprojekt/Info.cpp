#include "Info.h"
#include "WindowManager.h"
#include "tinyxml2.h"
#include "ResourceManager.h"
#include "FontMaster.h"

Info::Info(std::string elementName){
	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/Animalipedia/Animalipedia.xml");

	tinyxml2::XMLElement* elm = doc.FirstChildElement(elementName.c_str());

	sf::Texture* tex = ResourceManager::getInst().getTexture(elm->FirstChildElement("Image")->GetText());
	mPicture.setTexture(*tex);

	float x = elm->FirstChildElement("Image")->FloatAttribute("x");
	float y = elm->FirstChildElement("Image")->FloatAttribute("y");
	mPicture.setPosition(sf::Vector2f(x,y));
	//mPicture.setColor(sf::Color(255,255,255,175));

	mStandardText.setString(elm->FirstChildElement("StandardFact")->GetText());
	mStandardText.setPosition(400,150);
	mStandardText.setFont(FontMaster::sFont);
	mStandardText.setColor(sf::Color(0,0,0));
	mStandardText.setCharacterSize(18);

	mLockedText.setString(elm->FirstChildElement("LockedFact")->GetText());
	mLockedText.setPosition(400,410);
	mLockedText.setFont(FontMaster::sFont);
	mLockedText.setColor(sf::Color(0,0,0));
	mLockedText.setCharacterSize(18);

	mPadlock.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/Animalipedia/lock.png"));
	mPadlock.setPosition(sf::Vector2f(600,410));

	tinyxml2::XMLDocument docfacts;
	docfacts.LoadFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

	mExtraInfoUnlocked = docfacts.FirstChildElement(elementName.c_str())->BoolAttribute("extraUnlocked");
}

Info::~Info(){

}

void Info::setUnlockedInfo(bool boolean){
	mExtraInfoUnlocked = boolean;
}

void Info::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	window->draw(mPicture);
	window->draw(mStandardText);
	if(mExtraInfoUnlocked){
		window->draw(mLockedText);
	}else{
		window->draw(mPadlock);
	}
}

