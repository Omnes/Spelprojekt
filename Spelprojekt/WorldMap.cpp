#include "WorldMap.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include <SFML\Window\Keyboard.hpp>


WorldMap::WorldMap() : 
	mWorld(0),
	mSub(0),
	mLevelCount(0),
	mSection(0)
{

	readButtons();

	mMusic = "Resources/Sound/TitleScreen";

	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/WorldMenu/worldmap.png"));
	mSprite.setPosition(0,0);

	readSave();
	readWorld();
	updateWorld();
	readAnimals();

	mCurrentWorld = mWorld;
	mCurrentSection = mSection;
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

	doc.LoadFile("Resources/Data/Save/SavedGame.xml");// denna kommer inte funka sen n�r vi ska g�ra anv�ndare
	
	//laddar in vilken v�rld man �r p�. kollar om det finns ett elemnet eller inte(on�digt)
	tinyxml2::XMLElement *elm = doc.FirstChildElement("World");
	if(elm != 0){
		mWorld = elm->FirstAttribute()->IntValue();
	}else{
		std::cout<<"Sparfilen laddades inte"<<std::endl;
	}

	//kollar vilka v�rldar som �r br�nda(banor)
	tinyxml2::XMLElement *burnedLevel = doc.FirstChildElement("BurnedLevel");
	while(burnedLevel != 0){
		for(ButtonVector::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
			if(burnedLevel->FirstAttribute()->Value() == (*i)->getLevel()){
				//s�tter v�rlden till alive == false
				(*i)->setAlive(false);
			}
		}
		burnedLevel = burnedLevel->NextSiblingElement();
	}

	//kollar vilken section man �r p�
	tinyxml2::XMLElement *section = doc.FirstChildElement("Section");
	if(section != 0){
		mSection = section->FirstAttribute()->IntValue();
	}

	tinyxml2::XMLElement *dead = doc.FirstChildElement("DeadAnimals");
	if(dead != 0){
		mDeadAnimalVector.push_back(dead->FirstAttribute()->Value());
	}

}

void WorldMap::saveToFile(std::string currentLevel){
	
	tinyxml2::XMLDocument doc;
	
	// sparar vilken v�rld man �r p�
	tinyxml2::XMLElement* world = doc.NewElement("World"); // m�ste ha st�d gf�r att skapa filer
	world->SetAttribute("Worlds", mWorld);
	doc.LinkEndChild(world);

	//sparar d�da animaler
	if(mWorld > mCurrentWorld){
		std::vector<std::string> deadAnimals = *LevelManager::getInst().getDeadAnimalCollection();

		for(std::vector<std::string>::size_type i = 0; i < deadAnimals.size(); i++){

			tinyxml2::XMLElement* dead = doc.NewElement("DeadAnimals");
			dead->SetAttribute("Dead", deadAnimals[i].c_str());
			doc.LinkEndChild(dead);

		}
	}

	// tar emot vilken level man just var p�
	mBurnedLevelVector.push_back(currentLevel);
	//om man har g�tt vidare till n�sta v�rld. spara vilka v�rldar som har brunnit
	if(mWorld > mCurrentWorld){
		mSection = mCurrentSection;
		for(BurnedLevelVector::iterator i = mBurnedLevelVector.begin(); i != mBurnedLevelVector.end();i++){
			tinyxml2::XMLElement* burnedLevel = doc.NewElement("BurnedLevel");
			burnedLevel->SetAttribute("Level", (*i).c_str());
			doc.LinkEndChild(burnedLevel);
		}
		mBurnedLevelVector.clear();
		mCurrentWorld = mWorld;
	}

	// sparar vilken section man �r p�. kan l�gga denna inom ifsatsen och ta bort mSection(tror jag)
	tinyxml2::XMLElement* section = doc.NewElement("Section");
	section->SetAttribute("Level", mSection);
	doc.LinkEndChild(section);

	doc.SaveFile("Resources/Data/Save/SavedGame.xml"); //<------- variabel funkar h�r

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

//m�ste endast k�ras i konstruktorn
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


//m�ste k�ras efter varje klarade bana
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
		mCurrentSection++;
		mLevelCount = 0;
	}
	

	if(mWorldVector[mWorld].size() <= mSub){
		mWorld++;
		mSub = 0;
	}

	for(ButtonVector::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		if((*i)->getLevel() == currentLevel){
			//alive �r korrekt h�r
			(*i)->setAlive(false);
		}
	}

	updateWorld();
	saveToFile(currentLevel);
}

void WorldMap::readAnimals(){

	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/AnimalUnlock.xml");

	tinyxml2::XMLElement *section = doc.FirstChildElement();

	std::vector <std::string> fakeAnimals;

	/*section->FirstAttribute()->IntValue() <= mSection && */
	while(section != 0 && section->FirstAttribute()->IntValue() <= mSection){
		tinyxml2::XMLElement *animals = section->FirstChildElement();
		while(animals != 0){
			for(DeadAnimalVector::iterator i = mDeadAnimalVector.begin(); i != mDeadAnimalVector.end(); i++){
				if((*i) != animals->GetText()){
					fakeAnimals.push_back(animals->GetText());
				}
			}
			animals = animals->NextSiblingElement();
		}
		section = section->NextSiblingElement();
	}

	LevelManager::getInst().setAliveAnimals(fakeAnimals);
}

void WorldMap::readNewAnimals(){

	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/AnimalUnlock.xml");

	tinyxml2::XMLElement *section = doc.FirstChildElement();

	std::vector <std::string> fakeAnimals;

	while(section != 0){
		tinyxml2::XMLElement *animals = section->FirstChildElement();
		while(animals != 0 && section->FirstAttribute()->IntValue() == mCurrentSection){
			fakeAnimals.push_back(animals->GetText());
			animals = animals->NextSiblingElement();
		}
		section = section->NextSiblingElement();
	}
	LevelManager::getInst().addAliveAnimals(fakeAnimals);
}