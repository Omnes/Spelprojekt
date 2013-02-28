#include "PauseMeny.h"
#include "StateManager.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "LevelManager.h"
#include <SFML\Window\Keyboard.hpp>

PauseMeny::PauseMeny(): mRenderState(0), mResumeButton(sf::Vector2f(640,480),"popState","Resources/Misc/knapp1.jpg", "Resources/Sound/test.wav"){
	mRenderState = StateManager::getInst().getTop();
	mMusic = mRenderState->getMusic();
	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/PauseMenu/paused.png"));
	readFromFile();
}

PauseMeny::~PauseMeny(){

	while(!mAbilityButtons.empty()){

		delete	mAbilityButtons.back();
		mAbilityButtons.pop_back();
		
	}

}   

//se till att den är relativ till view! GJORT!!!!!
void PauseMeny::render(){
	if(mRenderState != 0){
		mRenderState->render();
	}

	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
	WindowManager::getInst().getWindow()->draw(mSprite);
	WindowManager::getInst().getWindow()->draw(mResumeButton.getSprite());
		for(std::vector<FakeAbilityButton*>::iterator i = mAbilityButtons.begin(); i != mAbilityButtons.end(); i++){
		(*i)->render();
	}

	
}

void PauseMeny::update(){
	mResumeButton.update();
		for(std::vector<FakeAbilityButton*>::iterator i = mAbilityButtons.begin(); i != mAbilityButtons.end(); i++){
		(*i)->update();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		EventManager::getInst().addEvent("popStateTwice");
	}
}

std::string PauseMeny::getMusic(){
	return mMusic;
}

void PauseMeny::readFromFile(){
		std::vector<std::string> abilities = LevelManager::getInst().getAbilitiesOnLevel();

	tinyxml2::XMLDocument doca;
	doca.LoadFile("Resources/Data/Abilities.xml");

	float abilityNumber = 0;

	sf::Vector2f startPosition = sf::Vector2f(140,615);
	sf::Vector2f distance = sf::Vector2f(200,0);
	sf::Vector2f distance2 = sf::Vector2f(150,0);

	sf::Vector2f position = startPosition;

	for(std::vector<std::string>::iterator i = abilities.begin(); i != abilities.end();i++){
		tinyxml2::XMLElement *elm = doca.FirstChildElement("Abilities")->FirstChildElement((*i).c_str());

		std::string atexture = elm->FirstChildElement("Texture")->GetText();

		std::string itexture = elm->FirstChildElement("InfoPicture")->GetText();

		if(abilityNumber != 0){
			if((int)abilityNumber % 2 == 1){
				position += distance;
			}else{
				position += distance2;
			}
		}

		mAbilityButtons.push_back(new FakeAbilityButton(position,atexture,itexture));

		abilityNumber++;
	}	
}

