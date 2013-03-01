#include "Info.h"
#include "WindowManager.h"
#include "tinyxml2.h"
#include "ResourceManager.h"

Info::Info(std::string elementName){
	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/Animalipedia/Animalipedia.xml");

	tinyxml2::XMLElement* elm = doc.FirstChildElement(elementName.c_str());

	sf::Texture* tex = ResourceManager::getInst().getTexture(elm->FirstChildElement("Image")->GetText());
	mPicture.setTexture(*tex);

	float x = elm->FirstChildElement("Image")->FloatAttribute("x");
	float y = elm->FirstChildElement("Image")->FloatAttribute("y");
	mPicture.setPosition(sf::Vector2f(x,y));

	mStandardText.setString(elm->FirstChildElement("StandardFact")->GetText());
	mStandardText.setPosition(150,64);

	mLockedText.setString(elm->FirstChildElement("LockedFact")->GetText());
	mLockedText.setPosition(150,360);

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

