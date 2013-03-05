#include "LevelTutorial.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "LevelManager.h"
 
LevelTutorial::LevelTutorial() 
	: mStartedTimer(false){
	mMusic = "Resources/Sound/TitleScreen";
	mTimer1.restart();
	mArrow.setTexture(*ResourceManager::getInst().getTexture("Resources/GUI/pil.png"));
	mArrow.setTextureRect(sf::IntRect(0,0, mArrow.getTexture()->getSize().x/10, mArrow.getTexture()->getSize().y));

	LevelManager::getInst().setFilePath("Resources/Data/Level/Jungle_Level1.xml");
	
	readAnimals();

	sf::Sprite loadingscreen(*ResourceManager::getInst().getTexture("Resources/Menu/LevelFinished.png"));
	WindowManager::getInst().getWindow()->draw(loadingscreen);
	WindowManager::getInst().getWindow()->display();
	mTaktik = new TaktikMeny;

	//spela ljud nr 1

	for(int i=0; i<5; i++){
		mArrows.push_back(mArrow);
	}

	setArrowPositions();
}

LevelTutorial::~LevelTutorial(){
	delete mTaktik;
}

void LevelTutorial::update(){

	//När ljud nr 1 spelats
	if(mTimer1.getElapsedTime().asSeconds() > 7/*ljudtid*/ && mTaktik->getFreeSpots()){
		mTaktik->update();
	}

	//Starta ljud nr 2
	if(mTaktik->getFreeSpots() == false && mStartedTimer == false){
		mTimer2.restart();
		mStartedTimer=true;
		//spela ljud
	}

	//När ljud nr 2 spelats
	if(mTimer2.getElapsedTime().asSeconds() > 5/*ljudtid*/){ 
		mTaktik->update();
	}


}

void LevelTutorial::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mTaktik->render();

	//pil 1
	if(mTimer1.getElapsedTime().asSeconds() > 2 && mTimer1.getElapsedTime().asSeconds() < 4){
	
		window->draw(mArrows[0]);		
	}
	
	//pil 2
	if(mTimer1.getElapsedTime().asSeconds() > 4 && mTimer1.getElapsedTime().asSeconds() < 6){
	
		window->draw(mArrows[1]);		
	}

	//pil 3
	if(mTimer2.getElapsedTime().asSeconds() > 1 && mTimer2.getElapsedTime().asSeconds() < 3 && mStartedTimer == true){
	
		window->draw(mArrows[2]);		
	}
	
	//pil 4
	if(mTimer2.getElapsedTime().asSeconds() > 3 && mTimer2.getElapsedTime().asSeconds() < 5 && mStartedTimer == true){
	
		window->draw(mArrows[3]);		
	}

}

std::string LevelTutorial::getMusic(){

	return mMusic;
}

void LevelTutorial::setArrowPositions(){
		
	mArrows[0].setPosition(100,100);
	mArrows[1].setPosition(200,100);
	mArrows[2].setPosition(300,100);
	mArrows[3].setPosition(100,200);
	mArrows[4].setPosition(100,300);
}

void LevelTutorial::readAnimals(){

	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/AnimalUnlock.xml");

	std::vector <std::string> fakeAnimals;

	tinyxml2::XMLElement *section = doc.FirstChildElement("Section");
	tinyxml2::XMLElement *animals = section->FirstChildElement();
	while(animals != 0){
		fakeAnimals.push_back(animals->GetText());
		animals = animals->NextSiblingElement();
	}

	LevelManager::getInst().setAliveAnimals(fakeAnimals);
}