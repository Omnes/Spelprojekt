#include "WorldMap.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include <SFML\Window\Keyboard.hpp>


WorldMap::WorldMap() : 
	mWorld(0),
	mSub(0),
	mLevelCount(0)
{

	readButtons();

	mMusic = "Resources/Sound/TitleScreen";

	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/WorldMenu/worldmap.png"));
	mSprite.setPosition(0,0);

	saveToFile();
	readWorld();
	updateWorld();
}

WorldMap::~WorldMap(){}

void WorldMap::update(){
	for (std::vector<LevelButton*>::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		(*i)->update();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		EventManager::getInst().addEvent("popState");
	}
}

void WorldMap::render(){
	
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
	window->draw(mSprite);
	
	for (std::vector<LevelButton*>::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		window->draw((*i)->getSprite());
	}
}

void WorldMap::readSave(){

	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Save/SavedGame.xml"); // denna kommer inte funka sen när vi ska göra användare

	tinyxml2::XMLElement *elm = doc.FirstChildElement("World");
	
	mWorld = elm->FirstAttribute()->IntValue();
}

void WorldMap::saveToFile(){
	
	tinyxml2::XMLDocument doc;

	////kanske skapar dokument. konstigt men funkar bra
	//tinyxml2::XMLElement* levelCompleted = doc.NewElement("LevelCompleted");

	//doc.LoadFile("Resources/Data/Save/SavedGame.xml");

	tinyxml2::XMLElement* world = doc.NewElement("World");
	world->SetAttribute("Worlds", mWorld);
	doc.LinkEndChild(world);

	doc.SaveFile("Resources/Data/Save/SavedGame.xml"); //<------- variabel funkar här

	readSave();

}

void WorldMap::readButtons(){

	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Menu/WorldMenu/Buttons.xml");

	tinyxml2::XMLElement *elm = doc.FirstChildElement();

	while(elm != 0){

		const tinyxml2::XMLAttribute *pos = elm->FirstChildElement("Position")->FirstAttribute();
		//position
		sf::Vector2f vect(pos->FloatValue(), pos->Next()->FloatValue());
		//event
		std::string evnt = elm->FirstChildElement("Event")->GetText();
		//images
		std::string images = elm->FirstChildElement("Images")->GetText();

		//bana xml-fil
		std::string bana = elm->FirstChildElement("Bana")->GetText();
		mButtonVector.push_back(new LevelButton(vect, evnt, images, bana));
		elm = elm->NextSiblingElement();
	}
}



std::string WorldMap::getMusic(){
	return mMusic;
}

//måste endast köras i konstruktorn
void WorldMap::readWorld(){
	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/Menu/WorldMenu/World.xml");
	tinyxml2::XMLElement *world = doc.FirstChildElement();

	while(world != 0){
		tinyxml2::XMLElement *sub = world->FirstChildElement();
		
		std::vector<std::vector<std::string>> SubVector;

		while(sub != 0){

			tinyxml2::XMLElement *level = sub->FirstChildElement();

			std::vector <std::string> LevelVector;

			while(level != 0){

				LevelVector.push_back(level->GetText());
				level = level->NextSiblingElement();
			}
			SubVector.push_back(LevelVector);
			sub = sub->NextSiblingElement();
		}
		mWorldVector.push_back(SubVector);
		world = world->NextSiblingElement();
	}
}


//måste köras efter varje klarade bana
void WorldMap::updateWorld(){
	for(int i = 0; i < 	mWorldVector[mWorld][mSub].size(); i++){
		for(ButtonVector::iterator j = mButtonVector.begin(); j != mButtonVector.end(); j++){

			if((mWorldVector[mWorld][mSub][i]) == (*j)->getLevel()){
				(*j)->setActive(true);
			}
		}
	}
}

void WorldMap::setCurrentWorldOrSub(std::string currentLevel){

	if(mWorldVector[mWorld][mSub].size() > mLevelCount){
		for(std::vector<std::string>::iterator i = mWorldVector.at(mWorld).at(mSub).begin(); i != mWorldVector.at(mWorld).at(mSub).end(); i++){
			if((*i) == currentLevel){
				mLevelCount++;
			}
		}
	}
	
	if(mWorldVector[mWorld][mSub].size() <= mLevelCount){
		//anger plats i vectorn. 
		mSub++;
		mLevelCount = 0;
	}
	

	if(mWorldVector[mWorld].size() <= mSub){
		mWorld++;
		mSub = 0;
	}

	for(ButtonVector::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		if((*i)->getLevel() == currentLevel){
			//alive är korrekt här
			(*i)->setAlive(false);
		}
	}
}