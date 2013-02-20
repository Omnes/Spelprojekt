#include "WorldMap.h"
#include "WindowManager.h"
WorldMap::WorldMap(){
	mButtonVector.push_back(new LevelButton(sf::Vector2f(250,500), "addTaktik","Resources/Misc/knapp1.jpg", "Resources/Data/Level/Jungle_Level1.xml"));
	mButtonVector.push_back(new LevelButton(sf::Vector2f(100,550), "addTaktik","Resources/Misc/knapp2.jpg", "Resources/Data/Level/Jungle_Level2.xml"));
	mButtonVector.push_back(new LevelButton(sf::Vector2f(300,550), "addTaktik","Resources/Misc/knapp3.jpg", "Resources/Data/Level/Jungle_Level3.xml"));
	mMusic = "Resources/Sound/TitleScreen";

	mTexture.loadFromFile("Resources/Menu/WorldMenu/worldmap.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(0,0);

	//mButtonVector.push_back(new LevelButton(sf::Vector2f(200,300), "addGameplay","knapp3.jpg","Resources/Data/Jungle_Level1.xml"));
	readFromFile();
}

WorldMap::~WorldMap(){}

void WorldMap::update(){
	for (std::vector<LevelButton*>::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		(*i)->update();
	}
}

void WorldMap::render(){
	
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
	window->draw(mSprite);
	
	for (std::vector<LevelButton*>::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		window->draw((*i)->getSprite());
	}
}

void WorldMap::readFromFile(){

	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Save/SavedGame.xml"); // denna kommer inte funka sen n�r vi ska g�ra anv�ndare

	tinyxml2::XMLElement *elm = doc.FirstChildElement();

	while(elm != 0){
		mPlayedLevels.push_back(elm->GetText());
		elm = elm->NextSiblingElement();
	}

	for(PlayedLevels::iterator i = mPlayedLevels.begin(); i != mPlayedLevels.end(); i++){
		for(ButtonVector::iterator j = mButtonVector.begin(); j != mButtonVector.end(); j++){
			if((*i) == (*j)->getLevel()){
				(*j)->setAlive(false);
				//kolla i LevelButton.cpp och fixa s� bilden �ndras i setAlive();
				//kolla ocks� LevelButton.cpp i update

			}
		}
	}
}

void WorldMap::saveToFile(std::string levelName){
	
	tinyxml2::XMLDocument doc;

	//kanske skapar dokument. konstigt men funkar bra
	tinyxml2::XMLElement* levelCompleted = doc.NewElement("LevelCompleted");

	doc.LoadFile("Resources/Data/Save/SavedGame.xml");

	levelCompleted->LinkEndChild(doc.NewText(levelName.c_str()));// variabel h�r <----------
	doc.LinkEndChild(levelCompleted);

	doc.SaveFile("Resources/Data/Save/SavedGame.xml"); //<------- variabel funkar h�r

	readFromFile();

}

std::string WorldMap::getMusic(){
	return mMusic;
}