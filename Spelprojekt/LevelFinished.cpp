#include "LevelFinished.h"
#include "LevelManager.h"
#include "tinyxml2.h"
#include "ResourceManager.h"
#include "WindowManager.h"

#include "StateManager.h"



LevelFinished::LevelFinished() : mButton(sf::Vector2f(500, 500), "goBackToWorld", "Resources/Misc/knapp1.jpg", "Resources/Sound/test.wav"){
	
	std::vector<std::string> Alive = LevelManager::getInst().getAliveAnimals();
	std::vector<std::string> Dead = LevelManager::getInst().getDeadAnimals();
	mAliveVector = loadAnimals(Alive);
	mDeadVector = loadAnimals(Dead);
	setPosition();

	mBackground.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/LevelFinished.png"));
	mMusic = "Resources/Sound/Level2_";

	mStampIndex = 0;
}

LevelFinished::~LevelFinished(){

}

void LevelFinished::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->draw(mBackground);


	for(std::vector<sf::Sprite*>::iterator i = mAliveVector.begin(); i != mAliveVector.end(); i++){
		window->draw(*(*i));
	}
	for(std::vector<sf::Sprite*>::iterator i = mDeadVector.begin(); i != mDeadVector.end(); i++){
		window->draw(*(*i));
	}

	window->draw(mButton.getSprite());

	for(std::vector<sf::Sprite*>::iterator i = mStampVector.begin(); i != mStampVector.end(); i++){
		window->draw(*(*i));
	}

}

void LevelFinished::update(){

	mButton.update();

	if(mStampIndex < mDeadVector.size() && mStampDelay.getElapsedTime().asSeconds() > 3){
		sf::Sprite* stamp = new sf::Sprite;
		stamp->setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/Utrotad.png"));
		stamp->setPosition(mDeadVector[mStampIndex]->getPosition());
		mStampVector.push_back(stamp);

		mStampDelay.restart();
		mStampIndex++;
	}

} 

std::vector<sf::Sprite*> LevelFinished::loadAnimals(std::vector<std::string> animalvector){

	ResourceManager *resourceManager = &ResourceManager::getInst();
	std::vector<sf::Sprite*>spriteVector;

	for(std::vector<std::string>::iterator i = animalvector.begin(); i != animalvector.end(); i++){

		tinyxml2::XMLDocument doc;
		doc.LoadFile((*i).c_str());

		tinyxml2::XMLElement *elm = doc.FirstChildElement("Animal")->FirstChildElement("Images");
		tinyxml2::XMLElement *elmf = doc.FirstChildElement("Animal")->FirstChildElement("ImageAttr");


		sf::Texture* tex = resourceManager->getTexture(elm->GetText());
		sf::Sprite *sprite = new sf::Sprite();
		sprite->setTexture(*tex);
		sprite->setTextureRect(sf::IntRect(0,0, tex->getSize().x/elmf->FirstAttribute()->Next()->FloatValue(), tex->getSize().y/2));
		spriteVector.push_back(sprite);
	}

	return spriteVector;
}

void LevelFinished::setPosition(){

	sf::Vector2f startpos(200,50);
	float distance = 100;

	for(int i = 0; i<mAliveVector.size(); i++){

		mAliveVector[i]->setPosition(startpos.x + distance * i, startpos.y);
	}

	for(int i = 0; i<mDeadVector.size(); i++){

		mDeadVector[i]->setPosition(startpos.x + distance * i, startpos.y + 100);
	}
}

std::string LevelFinished::getMusic(){
	return mMusic;
}


