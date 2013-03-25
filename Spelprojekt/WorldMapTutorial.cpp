#include "WorldMapTutorial.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "SoundManager.h"
#include "AchievementState.h"
 
WorldMapTutorial::WorldMapTutorial() {
	mMusic = "Resources/Sound/Music/Title_Screen_";
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

	StateManager::getInst().addState(new AchievementState(1));
	
	SoundManager::getInst().setMusicVolume(SoundManager::getInst().getCurrentPlaying()->getVolume()/10);

	mTutorialDuration = SoundManager::getInst().playVoice("Resources/Sound/Tutorial/Worldmap.wav").asSeconds();
	mTimer.restart();
}

WorldMapTutorial::~WorldMapTutorial(){

	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/Save/SavedGame.xml");

	if(!doc.FirstChildElement("Tutorial")){
		tinyxml2::XMLElement *tutorial = doc.NewElement("Tutorial");
		//den här kommer inte köras. kanske fixa, behövs ej
		if(!tutorial->Attribute("World")){
			tutorial->SetAttribute("World", false);
			doc.LinkEndChild(tutorial);	
		}
	}

	doc.SaveFile("Resources/Data/Save/SavedGame.xml");

}

void WorldMapTutorial::update(){

	if(mTimer.getElapsedTime().asSeconds() > 6){	

		mArrow.setPosition(-500, -500);

		if(mTimer.getElapsedTime().asSeconds() > 18.5){

			mArrow.setRotation(180);
			mArrow.setPosition(345,50);
		}
	}

	if(mTimer.getElapsedTime().asSeconds() > mTutorialDuration){
		StateManager::getInst().popState();
		SoundManager::getInst().loadSettings();
	}
}

void WorldMapTutorial::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mWorldMap->render();

	if(mTimer.getElapsedTime().asSeconds() > 4 && mTimer.getElapsedTime().asSeconds() < 20){

		window->draw(mArrow);

		if(mTimer.getElapsedTime().asSeconds() < 6){
		
			window->draw(mArrow2);
		}
	}
}

std::string WorldMapTutorial::getMusic(){

	return mMusic;
}

