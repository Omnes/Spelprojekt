#include "LevelFinished.h"
#include "LevelManager.h"
#include "tinyxml2.h"
#include "ResourceManager.h"
#include "WindowManager.h"


LevelFinished::LevelFinished() : mButton(sf::Vector2f(500, 500), "addStart", "knapp1.jpg"){
	
	std::vector<std::string> Alive = LevelManager::getInst().getAliveAnimals();
	std::vector<std::string> Dead = LevelManager::getInst().getDeadAnimals();
	mAliveVector = loadAnimals(Alive);
	mDeadVector = loadAnimals(Dead);
	setPosition();
}

LevelFinished::~LevelFinished(){

}

void LevelFinished::render(){


	for(std::vector<sf::Sprite*>::iterator i = mAliveVector.begin(); i != mAliveVector.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i));
	}
	for(std::vector<sf::Sprite*>::iterator i = mDeadVector.begin(); i != mDeadVector.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i));
	}

	WindowManager::getInst().getWindow()->draw(mButton.getSprite());

}

void LevelFinished::update(){

	mButton.update();

} 

std::vector<sf::Sprite*> LevelFinished::loadAnimals(std::vector<std::string> animalvector){

	ResourceManager *resourceManager = &ResourceManager::getInst();
	std::vector<sf::Sprite*>spriteVector;

	for(std::vector<std::string>::iterator i = animalvector.begin(); i != animalvector.end(); i++){

		tinyxml2::XMLDocument doc;
		doc.LoadFile((*i).c_str());

		tinyxml2::XMLElement *elm = doc.FirstChildElement("Animal")->FirstChildElement("Images");


		sf::Texture* tex = resourceManager->getTexture(elm->GetText());
		sf::Sprite *sprite = new sf::Sprite();
		sprite->setTexture(*tex);
		spriteVector.push_back(sprite);
	}

	return spriteVector;
}

void LevelFinished::setPosition(){

	sf::Vector2f startpos(200,200);
	float distance = 100;

	for(int i = 0; i<mAliveVector.size(); i++){

		mAliveVector[i]->setPosition(startpos.x + distance * i, startpos.y);
	}

	for(int i = 0; i<mDeadVector.size(); i++){

		mDeadVector[i]->setPosition(startpos.x + distance * i, startpos.y + 100);
	}
}
