#include "WorldMapTutorial.h"
#include "ResourceManager.h"
#include "WindowManager.h"
 
WorldMapTutorial::WorldMapTutorial() {
	mMusic = "Resources/Sound/TitleScreen";
	mTimer.restart();
	mArrow.setTexture(*ResourceManager::getInst().getTexture("Resources/GUI/pil.png"));
	mArrow.setTextureRect(sf::IntRect(0,0, mArrow.getTexture()->getSize().x/10, mArrow.getTexture()->getSize().y));

	sf::Sprite loadingscreen(*ResourceManager::getInst().getTexture("Resources/Menu/LevelFinished.png"));
	WindowManager::getInst().getWindow()->draw(loadingscreen);
	WindowManager::getInst().getWindow()->display();

	mWorldMap = dynamic_cast <WorldMap*> (StateManager::getInst().getTop());
	mWorldMap->update();
		
	//spela ljud 

	for(int i=0; i<5; i++){
		mArrows.push_back(mArrow);
	}

	setArrowPositions();
}

WorldMapTutorial::~WorldMapTutorial(){
}

void WorldMapTutorial::update(){

	//När ljudet spelats
	if(mTimer.getElapsedTime().asSeconds() > 7/*ljudtid*/){
		StateManager::getInst().popState();
	}
}

void WorldMapTutorial::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mWorldMap->render();

	//pil 1
	if(mTimer.getElapsedTime().asSeconds() > 2 && mTimer.getElapsedTime().asSeconds() < 4){
	
		window->draw(mArrows[0]);		
	}
	
	//pil 2
	if(mTimer.getElapsedTime().asSeconds() > 4 && mTimer.getElapsedTime().asSeconds() < 6){
	
		window->draw(mArrows[1]);		
	}
}

std::string WorldMapTutorial::getMusic(){

	return mMusic;
}

void WorldMapTutorial::setArrowPositions(){
		
	mArrows[0].setPosition(100,100);
	mArrows[1].setPosition(200,100);
	mArrows[2].setPosition(300,100);
	mArrows[3].setPosition(100,200);
	mArrows[4].setPosition(100,300);
}

