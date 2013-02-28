#include "TacticalVision.h"
#include "StateManager.h"
#include "WindowManager.h"
#include "LayerManager.h"
#include "LevelManager.h"


TacticalVision::TacticalVision() 
	: mRenderState(0)
	, mDuration(6){
	mRenderState = dynamic_cast<Gameplay*>(StateManager::getInst().getTop());
	mMusic = mRenderState->getMusic();
	mTimer.restart();
	mCamera = new TacticalVisionCamera(mRenderState->getLayerManager());
	readFromFile();
	
}

TacticalVision::~TacticalVision(){

	while(!mAbilityButtons.empty()){

		delete mAbilityButtons.back();
		mAbilityButtons.pop_back();
	}

	delete mCamera;
}

void TacticalVision::update(){

	for(std::vector<FakeAbilityButton*>::iterator i = mAbilityButtons.begin(); i != mAbilityButtons.end(); i++){
		(*i)->update();
	}
	
	if(mTimer.getElapsedTime().asSeconds() < mDuration-1){

		mCamera->update();
	}else{
		mCamera->moveBackToStartPosition();
	}

	if(mTimer.getElapsedTime().asSeconds() > mDuration){

		StateManager::getInst().popState();
	}

	
}
	
void TacticalVision::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->setView(*mCamera->getView());


	if(mRenderState != 0){
		mRenderState->renderFromTacVision();
	}

	for(std::vector<FakeAbilityButton*>::iterator i = mAbilityButtons.begin(); i != mAbilityButtons.end(); i++){
		(*i)->render();
	}
	
}

std::string TacticalVision::getMusic(){
	return mMusic;
}

void TacticalVision::readFromFile(){

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