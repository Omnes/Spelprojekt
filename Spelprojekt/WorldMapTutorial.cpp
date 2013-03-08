#include "WorldMapTutorial.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "SoundManager.h"
 
WorldMapTutorial::WorldMapTutorial() {
	mMusic = "Resources/Sound/TitleScreen";
	mArrow.setTexture(*ResourceManager::getInst().getTexture("Resources/GUI/pil.png"));
	mArrow.setTextureRect(sf::IntRect(0,0, mArrow.getTexture()->getSize().x/10, mArrow.getTexture()->getSize().y));
	mArrow.setOrigin(mArrow.getTexture()->getSize().x/20, mArrow.getTexture()->getSize().y/2);
	mArrow.setRotation(90);
	mArrow.setPosition(190,435);

	mArrow2.setTexture(*ResourceManager::getInst().getTexture("Resources/GUI/pil.png"));
	mArrow2.setTextureRect(sf::IntRect(0,0, mArrow2.getTexture()->getSize().x/10, mArrow2.getTexture()->getSize().y));
	mArrow2.setOrigin(mArrow2.getTexture()->getSize().x/20, mArrow2.getTexture()->getSize().y/2);
	mArrow2.setRotation(180);
	mArrow2.setPosition(550,610);

	sf::Sprite loadingscreen(*ResourceManager::getInst().getTexture("Resources/Menu/LevelFinished.png"));
	WindowManager::getInst().getWindow()->draw(loadingscreen);
	WindowManager::getInst().getWindow()->display();

	mWorldMap = dynamic_cast <WorldMap*> (StateManager::getInst().getTop());
	mWorldMap->update();
	
	SoundManager::getInst().setMusicVolume(10);

	mTutorialDuration = SoundManager::getInst().playVoice("Resources/Sound/Tutorial/Worldmap.ogg").asSeconds();
	mTimer.restart();
}

WorldMapTutorial::~WorldMapTutorial(){
}

void WorldMapTutorial::update(){

	if(mTimer.getElapsedTime().asSeconds() > 5){	

		mArrow.setPosition(-500, -500);

		if(mTimer.getElapsedTime().asSeconds() > 20){

			mArrow.setRotation(180);
			mArrow.setPosition(240,145);
		}
	}

	if(mTimer.getElapsedTime().asSeconds() > mTutorialDuration){
		StateManager::getInst().popState();
		SoundManager::getInst().setMusicVolume(100);
	}
}

void WorldMapTutorial::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mWorldMap->render();

	if(mTimer.getElapsedTime().asSeconds() > 3 && mTimer.getElapsedTime().asSeconds() < 23){

		window->draw(mArrow);

		if(mTimer.getElapsedTime().asSeconds() < 5){
		
			window->draw(mArrow2);
		}
	}
}

std::string WorldMapTutorial::getMusic(){

	return mMusic;
}

