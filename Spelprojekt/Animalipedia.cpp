#include "Animalipedia.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "tinyxml2.h"


Animalipedia::Animalipedia()
	: mBackground(*ResourceManager::getInst().getTexture("Resources/Menu/LevelFinished.png"))
	, mCurrentButtonPage(0)
	, mButtonsPerPage(5)
	, mUpButton(sf::Vector2f(0,0),1,"Resources/Menu/knapp.png","",this)
	, mDownButton(sf::Vector2f(0,600),-1,"Resources/Menu/knapp.png","",this){

		mMusic = "Resources/Sound/TitleScreen";
		loadUnlocked();
		mInfo = 0;
		setPage(mCurrentButtonPage);

		mButton = new Button(sf::Vector2f(1100,100), "popState", "Resources/Menu/knapp.png", "");
}



void Animalipedia::update(){
	for(std::vector<AnimalipediaButton*>::iterator i = mActiveButtons.begin();i != mActiveButtons.end(); i++){
		(*i)->update();
	}

	mButton->update();
	mUpButton.update();
	mDownButton.update();
}

void Animalipedia::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	window->draw(mBackground);

	if(mInfo != 0){
		mInfo->render();
	}
	
	for(std::vector<AnimalipediaButton*>::iterator i = mActiveButtons.begin();i != mActiveButtons.end(); i++){
		(*i)->render();
	}

	window->draw(mButton->getSprite());
	window->draw(mUpButton.getSprite());
	window->draw(mDownButton.getSprite());
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

		button->setLocked(elm->FloatAttribute("unlocked"));
		button->setNewInfo(elm->FloatAttribute("newFacts"));

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

void Animalipedia::setPage(int number){

	//gråa ut knapparna när vi inte kan gå längre

	if(mButtonVector.size() > number*mButtonsPerPage && number >= 0){
	
		mCurrentButtonPage = number;
		mActiveButtons.clear();

		int startX = 0;
		int startY = 100;
		int yDistance = 64;

		for (int i = 0; i < mButtonsPerPage; i++){
			if(i + number*mButtonsPerPage < mButtonVector.size()){
				mActiveButtons.push_back(mButtonVector[i + number*mButtonsPerPage]);
				mActiveButtons.back()->setPosition(sf::Vector2f(startX,startY + yDistance*i));
			}
		}
	}
}

int Animalipedia::getPage(){
	return mCurrentButtonPage;
}