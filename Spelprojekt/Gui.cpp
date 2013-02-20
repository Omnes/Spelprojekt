#include "Gui.h"
#include "ResourceManager.h"
#include "RemoveObstacleButton.h"
#include "WindowManager.h"
#include "TacticalVisionButton.h"
#include "InnerBeastButton.h"
#include <string>
#include "ParticleManager.h"
#include "LevelManager.h"
#include "tinyxml2.h"

Gui::Gui(): mWindow(WindowManager::getInst().getWindow()){

	ParticleManager* particleManager = &ParticleManager::getInst();
	particleManager->loadPrototype("Resources/Data/Particle/heartParticle.xml");
	particleManager->loadPrototype("Resources/Data/Particle/dirtParticle.xml");

	loadAbilites();

	mGuiSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Misc/Ui.png"));
	mGuiSprite.setPosition(sf::Vector2f(0,720-72));
}

void Gui::update(){
	for(AbilityButtons::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->update();
	}
}
void Gui::render(){
	mWindow->draw(mGuiSprite);
	for(AbilityButtons::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		mWindow->draw(*(*i)->getSprite());
	}
}

void Gui::unclickAll(){
	for(AbilityButtons::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->setClicked(false);
	}
}

void Gui::loadAbilites(){
	std::vector<std::string> abilities = LevelManager::getInst().getAbilitiesOnLevel();

	tinyxml2::XMLDocument doc;
	doc.LoadFile("Resources/Data/Abilities.xml");

	float abilityNumber = 0;

	sf::Vector2f startPosition = sf::Vector2f(100,600);
	sf::Vector2f distance = sf::Vector2f(200,0);

	for(std::vector<std::string>::iterator i = abilities.begin(); i != abilities.end();i++){
		tinyxml2::XMLElement *elm = doc.FirstChildElement("Abilities")->FirstChildElement((*i).c_str());

		std::string texture = elm->FirstChildElement("Texture")->GetText();

		std::string type = elm->FirstChildElement("Type")->GetText();

		sf::Vector2f position = startPosition + distance * abilityNumber;

		if(type == "Vision"){
			mButtons.push_back(new TacticalVisionButton(position,texture,this));
		}
		if(type == "Speed"){
			mButtons.push_back(new InnerBeastButton(position,texture,this));
		}
		if(type == "Remove"){
			std::vector<std::string> canRemoveVector;
			tinyxml2::XMLElement *canRemove = elm->FirstChildElement("CanRemove")->FirstChildElement();

			std::string effekt = elm->FirstChildElement("ParticleEffekt")->GetText();
			int amount = elm->FirstChildElement("ParticleEffekt")->FirstAttribute()->IntValue();

			while (canRemove != 0){
				canRemoveVector.push_back(canRemove->GetText());
				canRemove = canRemove->NextSiblingElement();
			}

			mButtons.push_back(new RemoveObstacleButton(canRemoveVector,position,texture,effekt,amount,this));
		}

		abilityNumber++;
	}

}

Gui::~Gui(){}