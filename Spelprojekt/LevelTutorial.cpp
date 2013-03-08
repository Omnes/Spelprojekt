#include "LevelTutorial.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include <SFML\Window\Keyboard.hpp>
 
LevelTutorial::LevelTutorial() 
	: mStartedTimer(false)
	, mStep1(1)
	, mStep2(1)
	, mStep3(1)
	, mS1Played(false){
	
		mMusic = "Resources/Sound/TitleScreen";
		
		mArrow.setTexture(*ResourceManager::getInst().getTexture("Resources/GUI/pil.png"));
		mArrow.setTextureRect(sf::IntRect(0,0, mArrow.getTexture()->getSize().x/10, mArrow.getTexture()->getSize().y));
		mArrow.setPosition(230,110);
		mArrow.setRotation(180);
		mArrow.setOrigin(mArrow.getTexture()->getSize().x/20, mArrow.getTexture()->getSize().y/2);

		mSpot.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/TacticMenu/spot.png"));
		mSpot.setPosition(85,300);
		mSpot.setOrigin(mSpot.getTexture()->getSize().x/2, mSpot.getTexture()->getSize().y/2);

		mObst1.setTexture(*ResourceManager::getInst().getTexture("Resources/GUI/manmade.png"));
		mObst1.setPosition(390, 515);

		mObst2.setTexture(*ResourceManager::getInst().getTexture("Resources/GUI/nature.png"));
		mObst2.setPosition(690, 515);

		mSteer.setTexture(*ResourceManager::getInst().getTexture("Resources/Misc/piltangent.png"));
		mSteer.setOrigin(mSteer.getTexture()->getSize().x/2,mSteer.getTexture()->getSize().y/2);
		mSteer.setPosition(500,380);

		mScroll.setTexture(*ResourceManager::getInst().getTexture("Resources/Misc/scroller.png"));
		mScroll.setOrigin(mSteer.getTexture()->getSize().x/2,mSteer.getTexture()->getSize().y/2);
		mScroll.setPosition(500,380);

		LevelManager::getInst().setFilePath("Resources/Data/Level/Jungle_Level1.xml");
		
		readAnimals();


		sf::Sprite loadingscreen(*ResourceManager::getInst().getTexture("Resources/Menu/LevelFinished.png"));
		WindowManager::getInst().getWindow()->draw(loadingscreen);
		WindowManager::getInst().getWindow()->display();
		mTaktik = new TaktikMeny;

		mTimer1.restart();
		SoundManager::getInst().setMusicVolume(10);
		mIntroLength = SoundManager::getInst().playVoice("Resources/Sound/Tutorial/Intro.ogg").asSeconds();

}

LevelTutorial::~LevelTutorial(){
	delete mTaktik;
}

void LevelTutorial::update(){

	

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	//När introt spelats 
	if(mTimer1.getElapsedTime().asSeconds() > mIntroLength){
	
		//Spela steg 1
		if(mS1Played == false){
			mStep1 = SoundManager::getInst().playVoice("Resources/Sound/Tutorial/Step1.ogg").asSeconds();
			mS1Played = true;
		}
		
		if(mTimer1.getElapsedTime().asSeconds() > mIntroLength + 3.5){

			mArrow.setPosition(230,300);

			if(mTimer1.getElapsedTime().asSeconds() > mIntroLength + 5.0){

				mArrow.setPosition(230,515);

				if(mTimer1.getElapsedTime().asSeconds() > mIntroLength + 6){
				
					mArrow.setRotation(0);
					mArrow.setPosition(510,140);

					if(mTimer1.getElapsedTime().asSeconds() > mIntroLength + 9.5){
						
						mArrow.setPosition(-500, -500);

						if(mTimer1.getElapsedTime().asSeconds() > mIntroLength + 13.5){
						
							sf::Color color(0,255,0,255);
							mSpot.setColor(color);
						}
					}
				}
			}
		}
		
		//När ljud nr 1 spelats
		if(mTimer1.getElapsedTime().asSeconds() > mIntroLength + mStep1 && mTaktik->getFreeSpots()){
			mTaktik->update();
		}
	}

	//Starta ljud nr 2
	if(mTaktik->getFreeSpots() == false && mStartedTimer == false){
		mStartedTimer=true;
		mStep2 = SoundManager::getInst().playVoice("Resources/Sound/Tutorial/Step2.ogg").asSeconds();
		mTimer2.restart();
	}

	if(mTimer2.getElapsedTime().asSeconds() > 7 && mStartedTimer == true){
	
		mArrow.setRotation(90);
		mArrow.setPosition(530, 530); 

		if(mTimer2.getElapsedTime().asSeconds() > 9){
		
			mArrow.setPosition(725, 530);

			if(mTimer2.getElapsedTime().asSeconds() > 12){
		
				mArrow.setPosition(-500, -500);
	
				if(mTimer2.getElapsedTime().asSeconds() > 13.5){

					mArrow.setPosition(175, 530);

					if(mTimer2.getElapsedTime().asSeconds() > 15){
					
						mArrow.setPosition(-500, -500);

						if(mTimer2.getElapsedTime().asSeconds() > 17){
						
							mArrow.setPosition(380, 530);

							if(mTimer2.getElapsedTime().asSeconds() > 18){
								
								mArrow.setPosition(-500,-500);

								if(mTimer2.getElapsedTime().asSeconds() > 34.5){

									mArrow.setPosition(1010, 540);

									if(mTimer2.getElapsedTime().asSeconds() > 37){

										mArrow.setPosition(-500, -500);

										if(mTimer2.getElapsedTime().asSeconds() > mStep2){	
											
											mTaktik->update();
											SoundManager::getInst().loadSettings();
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)){
		StateManager::getInst().popState();
	}
}

void LevelTutorial::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mTaktik->render();

	if(mTimer1.getElapsedTime().asSeconds() > mIntroLength + 2){
	
		window->draw(mArrow);		
	}

	if(mTimer1.getElapsedTime().asSeconds() > mIntroLength + 10.5 && mTimer1.getElapsedTime().asSeconds() < mIntroLength + 17){
						
		window->draw(mSpot);
	}
	
	if(mTimer2.getElapsedTime().asSeconds() > 20 && mTimer2.getElapsedTime().asSeconds() < 26 && mStartedTimer == true){

		window->draw(mObst1);
		window->draw(mObst2);
	}

	if(mTimer2.getElapsedTime().asSeconds() > 28.5 && mTimer2.getElapsedTime().asSeconds() < 32 && mStartedTimer == true){

		window->draw(mSteer);
	}
	
	if(mTimer2.getElapsedTime().asSeconds() > 32 && mTimer2.getElapsedTime().asSeconds() < 34 && mStartedTimer == true){

		window->draw(mScroll);
	}
}

std::string LevelTutorial::getMusic(){

	return mMusic;
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