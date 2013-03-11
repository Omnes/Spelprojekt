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

	loadAbilites();

	mGuiSprite.setTexture(*ResourceManager::getInst().getTexture(LevelManager::getInst().getGuiTextureFilepath()));
	mGuiSprite.setPosition(sf::Vector2f(0,0));

	std::vector<std::string>* deadAnimalCollection = LevelManager::getInst().getDeadAnimalCollection();
	
	//skitkod skiter sig hårt när vi har mer än 1 dött djur <- fixa detta om det blir ett problem... så mycket fel med den här kodbiten
	for(std::vector<std::string>::iterator i = deadAnimalCollection->begin(); i != deadAnimalCollection->end();i++){
		tinyxml2::XMLDocument doc;
		doc.LoadFile((*i).c_str());
		sf::Sprite* sprite = new sf::Sprite(*ResourceManager::getInst().getTexture(doc.FirstChildElement()->FirstChildElement("Images")->GetText()));
		sprite->setTextureRect(sf::IntRect(0,0,sprite->getTexture()->getSize().x/10,sprite->getTexture()->getSize().y/2));
		sprite->setPosition(1100,608);
		sprite->setScale(0.65,0.65);
		mExtinct.setPosition(1120,625);
		mExtinct.setScale(0.4,0.4);
		mDeadAnimals.push_back(sprite);
	}

	mExtinct.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/GameOverMenu/Extinct.png"));
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

	for(std::vector<sf::Sprite*>::iterator i = mDeadAnimals.begin(); i != mDeadAnimals.end(); i++){
		mWindow->draw(*(*i));
		mWindow->draw(mExtinct);
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

	sf::Vector2f startPosition = sf::Vector2f(140,615);
	sf::Vector2f distance = sf::Vector2f(200,0);
	sf::Vector2f distance2 = sf::Vector2f(150,0);

	sf::Vector2f position = startPosition;

	for(std::vector<std::string>::iterator i = abilities.begin(); i != abilities.end();i++){
		tinyxml2::XMLElement *elm = doc.FirstChildElement("Abilities")->FirstChildElement((*i).c_str());

		std::string texture = elm->FirstChildElement("Texture")->GetText();

		std::string type = elm->FirstChildElement("Type")->GetText();

		std::string sound = elm->FirstChildElement("Sound")->Attribute("onUse");

		if(abilityNumber != 0){
			if((int)abilityNumber % 2 == 1){
				position += distance;
			}else{
				position += distance2;
			}
		}

		if(type == "Vision"){
			float cooldown = elm->FirstChildElement("Stats")->FloatAttribute("cooldown");
			mButtons.push_back(new TacticalVisionButton(position,texture,cooldown,sound,this));
		}

		if(type == "Speed"){

			float cooldown = elm->FirstChildElement("Stats")->FloatAttribute("cooldown");
			float speedIncrease = elm->FirstChildElement("Stats")->FloatAttribute("speedIncrease");
			float duration = elm->FirstChildElement("Stats")->FloatAttribute("duration");

			mButtons.push_back(new InnerBeastButton(position,texture,cooldown,speedIncrease,duration,sound,this));
		}

		if(type == "Remove"){

			std::string effekt = elm->FirstChildElement("ParticleEffekt")->GetText();
			int amount = elm->FirstChildElement("ParticleEffekt")->IntAttribute("amount");
			float cooldown = elm->FirstChildElement("Stats")->FloatAttribute("cooldown");

			std::vector<std::string> canRemoveVector;
			tinyxml2::XMLElement *canRemove = elm->FirstChildElement("CanRemove")->FirstChildElement();

			while (canRemove != 0){
				canRemoveVector.push_back(canRemove->GetText());
				canRemove = canRemove->NextSiblingElement();
			}

			mButtons.push_back(new RemoveObstacleButton(canRemoveVector,position,texture,cooldown,effekt,amount,sound,this));
		}

		abilityNumber++;
	}

}

Gui::~Gui(){

	unclickAll();
	while(!mButtons.empty()){
		delete mButtons.back();
		mButtons.pop_back();
	}
	while(!mDeadAnimals.empty()){
		delete mDeadAnimals.back();
		mDeadAnimals.pop_back();
	}
}