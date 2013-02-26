#include "Animalipedia.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "tinyxml2.h"


Animalipedia::Animalipedia()
	: mBackground(*ResourceManager::getInst().getTexture("Resources/Menu/LevelFinished.png")){

		mMusic = "Resources/Sound/TitleScreen";
		loadUnlocked();
		mInfo = 0;
}



void Animalipedia::update(){
	for(std::vector<AnimalipediaButton*>::iterator i = mButtonVector.begin();i != mButtonVector.end(); i++){
		(*i)->update();
	}
}

void Animalipedia::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	window->draw(mBackground);

	if(mInfo != 0){
		mInfo->render();
	}
	
	for(std::vector<AnimalipediaButton*>::iterator i = mButtonVector.begin();i != mButtonVector.end(); i++){
		(*i)->render();
	}

}

Animalipedia::~Animalipedia(){

}

std::string Animalipedia::getMusic(){
	return mMusic;
}

void Animalipedia::loadUnlocked(){

	tinyxml2::XMLDocument unlockedDoc;
	unlockedDoc.LoadFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

	tinyxml2::XMLDocument wikiDoc;
	wikiDoc.LoadFile("Resources/Data/Animalipedia/Animalipedia.xml");

	tinyxml2::XMLElement* elm = unlockedDoc.FirstChildElement();
	int count = 0;
	
	while(elm != 0){

		count++;

		sf::Vector2f pos = sf::Vector2f(0,100*count);
		std::string page = elm->Name();
		std::string title = wikiDoc.FirstChildElement(page.c_str())->FirstChildElement("Title")->GetText();
		std::string sound = "Resources/Data/Sound/test.wav";
	 
		AnimalipediaButton* button = new AnimalipediaButton(pos,page,title,sound,this);

		button->setLocked(elm->FirstAttribute()->IntValue());
		button->setNewInfo(elm->FirstAttribute()->Next()->BoolValue());

		mButtonVector.push_back(button);

	 	elm = elm->NextSiblingElement();

	}
}

void Animalipedia::setInfo(std::string name){
	mInfoName = name;
	if(mInfo != 0){
		delete mInfo;
	}
	mInfo = new Info(name);
	
}

std::string Animalipedia::getInfo(){
	return mInfoName;
}