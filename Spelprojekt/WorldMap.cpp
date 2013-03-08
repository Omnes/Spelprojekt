#include "WorldMap.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include <SFML\Window\Keyboard.hpp>
#include "StateManager.h"
#include "Cutscene.h"



WorldMap::WorldMap() : 
	mWorld(0),
	mSub(0),
	mLevelCount(0),
	mSection(0),
	mCount(0)
{

	readButtons();

	mMusic = "Resources/Sound/Music/TitleScreen";

	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/WorldMenu/WorldmapBG.png"));
	mSprite.setPosition(0,0);

	readSave();
	readWorld();
	updateWorld();
	readAnimals();
	LevelManager::getInst().setDeadAnimalCollection(mDeadAnimalVector);

	mCurrentWorld = mWorld;
	mCurrentSection = mSection;

	mButton = new Button(sf::Vector2f(100,100), "addAnimalipedia", "Resources/Menu/knapp.png", "");

	mCutscenes.push_back("Resources/Data/Cutscenes/Cutscene_1.xml");
	mCutscenes.push_back("Resources/Data/Cutscenes/Cutscene_2.xml");
	mCutscenes.push_back("Resources/Data/Cutscenes/Cutscene_3.xml");

}

WorldMap::~WorldMap(){}

void WorldMap::update(){

	mButton->update();

	for (std::vector<LevelButton*>::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		(*i)->update();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		EventManager::getInst().addEvent("popState");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
		for (std::vector<LevelButton*>::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
			(*i)->setActive(true);
		}
	}
}

void WorldMap::render(){
	
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
	window->draw(mSprite);
	
	window->draw(mButton->getSprite());

	for (std::vector<LevelButton*>::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		window->draw((*i)->getSprite());
	}
}

void WorldMap::readSave(){

	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Save/SavedGame.xml");// denna kommer inte funka sen när vi ska göra användare
	
	//laddar in vilken värld man är på. kollar om det finns ett elemnet eller inte(onödigt)
	tinyxml2::XMLElement *elm = doc.FirstChildElement("World");
	if(elm != 0){
		mWorld = elm->FirstAttribute()->IntValue();
	}else{
		std::cout<<"Sparfilen laddades inte"<<std::endl;
	}

	//kollar vilka världar som är brända(banor)
	tinyxml2::XMLElement *burnedLevel = doc.FirstChildElement("BurnedLevel");
	while(burnedLevel != 0){
		for(ButtonVector::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
			if(burnedLevel->FirstAttribute()->Value() == (*i)->getLevel()){
				//sätter världen till alive == false
				(*i)->setAlive(false);
			}
		}
		burnedLevel = burnedLevel->NextSiblingElement();
	}

	//kollar vilken section man är på
	tinyxml2::XMLElement *section = doc.FirstChildElement("Section");
	if(section != 0){
		mSection = section->FirstAttribute()->IntValue();
	}

	tinyxml2::XMLElement *dead = doc.FirstChildElement("DeadAnimals");
	if(dead != 0){
		dead = dead->FirstChildElement("Animal");
		mDeadAnimalVector.push_back(dead->FirstAttribute()->Value());
		dead->NextSiblingElement();
	}

}

void WorldMap::saveToFile(std::string currentLevel){
	
	tinyxml2::XMLDocument doc;
	
	doc.LoadFile("Resources/Data/Save/SavedGame.xml");


	// sparar vilken värld man är på
	tinyxml2::XMLElement* world;
	if(doc.FirstChildElement("World")){
		world = doc.FirstChildElement("World"); // måste ha stöd gför att skapa filer
		world->SetAttribute("Worlds", mWorld);
	}else{
		world = doc.NewElement("World"); // måste ha stöd gför att skapa filer
		world->SetAttribute("Worlds", mWorld);
		doc.LinkEndChild(world);
	}

	// tar emot vilken level man just var på
	mBurnedLevelVector.push_back(currentLevel);

	if(mWorld > mCurrentWorld){

		//sparar döda animaler
		for(DeadAnimalVector::iterator i = mDeadAnimalVector.begin(); i != mDeadAnimalVector.end();i++){

			std::string deadAnimal = "";
			tinyxml2::XMLElement* deadExist;

			//kollar om elemntent finns
			if(doc.FirstChildElement("DeadAnimals")){
				tinyxml2::XMLElement* temp = doc.FirstChildElement("DeadAnimals");
				//kollar om elemntent finns
				if(temp->FirstChildElement("Animal")){
					deadExist = doc.FirstChildElement("DeadAnimals")->FirstChildElement(); // ändra sen till en for()
					deadAnimal = deadExist->Attribute("Dead");
				}
			}

			if(deadAnimal != (*i).c_str()){

				tinyxml2::XMLElement* deadA;

				if(doc.FirstChildElement("DeadAnimals")){
					deadA = doc.FirstChildElement("DeadAnimals");
				}{
					deadA = doc.NewElement("DeadAnimals");
					doc.LinkEndChild(deadA);
				}

					tinyxml2::XMLElement* newDead = doc.NewElement("Animal");
					newDead->SetAttribute("Dead", (*i).c_str());
					deadA->LinkEndChild(newDead);

			}
		}

		//om man har gått vidare till nästa värld. spara vilka världar som har brunnit
		for(BurnedLevelVector::iterator i = mBurnedLevelVector.begin(); i != mBurnedLevelVector.end();i++){
			tinyxml2::XMLElement* burnedLevel = doc.NewElement("BurnedLevel");
			burnedLevel->SetAttribute("Level", (*i).c_str());
			doc.LinkEndChild(burnedLevel);
		}
		mBurnedLevelVector.clear();

		//if(mWorld > mCurrentWorld){
		//	EventManager::getInst().addEvent("cutscene_1");
		//}

		mCurrentWorld = mWorld;
		mSection = mCurrentSection;
	}

	// sparar vilken section man är på. kan lägga denna inom ifsatsen och ta bort mSection(tror jag)
	tinyxml2::XMLElement* section;
	if(doc.FirstChildElement("Section")){
		section = doc.FirstChildElement("Section");
		section->SetAttribute("Level", mSection);
	}else{
		section = doc.NewElement("Section");
		section->SetAttribute("Level", mSection);
		doc.LinkEndChild(section);
	}

	doc.SaveFile("Resources/Data/Save/SavedGame.xml"); //<------- variabel funkar här
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
				mCurrentSection++;
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
		StateManager::getInst().addState(new Cutscene(mCutscenes[mWorld-1])); //hårdkodade cutscenes ohoy!
		
	}

	for(ButtonVector::iterator i = mButtonVector.begin(); i != mButtonVector.end(); i++){
		if((*i)->getLevel() == currentLevel){
			//alive är korrekt här
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

	while(section != 0 && section->FirstAttribute()->IntValue() <= mSection){
		tinyxml2::XMLElement *animals = section->FirstChildElement();
		while(animals != 0){
			fakeAnimals.push_back(animals->GetText());
			animals = animals->NextSiblingElement();
		}
		section = section->NextSiblingElement();
	}

	if(!mDeadAnimalVector.empty()){
		for(DeadAnimalVector::iterator i = mDeadAnimalVector.begin(); i != mDeadAnimalVector.end(); i++){
			for(std::vector<std::string>::iterator j = fakeAnimals.begin(); j != fakeAnimals.end();){
				if((*i) == (*j)){
					j = fakeAnimals.erase(j);
				}else{
					j++;
				}
			}
		}
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

void WorldMap::setDeadAnimals(std::vector <std::string> deadAnimals){
	for(std::vector<std::string>::iterator i = deadAnimals.begin(); i != deadAnimals.end(); i++){
		mDeadAnimalVector.push_back((*i));
	}
}