#include "AchievementState.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "SoundManager.h"
#include "StateManager.h"


AchievementState::AchievementState(int section){

	mPreState = StateManager::getInst().getTop();
	mMusic = mPreState->getMusic();

	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/AchievementMenu/unlock.png"));
	mSprite.setPosition(50,50);

	sf::Vector2f buttonPos = sf::Vector2f(mSprite.getTexture()->getSize().x/2, mSprite.getTexture()->getSize().y - 200);

	mButton = new Button(sf::Vector2f(buttonPos.x - 125, buttonPos.y), "popState", "Resources/Menu/AchievementMenu/okejknapp.png", "sound");

	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/AnimalUnlock.xml");
	tinyxml2::XMLElement *sect = doc.FirstChildElement("Section");

	while(sect != 0){
		const tinyxml2::XMLElement *animal = sect->FirstChildElement();
		if(sect->IntAttribute("level") == section){
			while(animal != 0){
				mAnimalVector.push_back(animal->GetText());
				animal = animal->NextSiblingElement();
			}
			break;
		}
		sect = sect->NextSiblingElement();
	}

	ResourceManager *resourceManager = &ResourceManager::getInst();

	for(std::vector<std::string>::iterator i = mAnimalVector.begin(); i != mAnimalVector.end(); i++){
		doc.LoadFile((*i).c_str());

		tinyxml2::XMLElement *elm = doc.FirstChildElement("Animal")->FirstChildElement("Images");
		tinyxml2::XMLElement *elmf = doc.FirstChildElement("Animal")->FirstChildElement("ImageAttr");

		tinyxml2::XMLElement *name = doc.FirstChildElement()->FirstChildElement("Name");
		//mUnlockVector.push_back(name->GetText());

		sf::Texture* tex = resourceManager->getTexture(elm->GetText());
		sf::Sprite *sprite = new sf::Sprite();
		sprite->setTexture(*tex);
		sprite->setTextureRect(sf::IntRect(0,0, tex->getSize().x/elmf->IntAttribute("frames"), tex->getSize().y/2));

		mImageVector.push_back(sprite);
	}

	int startPosX = 350;
	int startPosY = 350;

	//kanske onödig
	for(std::vector<sf::Sprite*>::size_type i = 0; i < mImageVector.size(); i++){
		mImageVector[i]->setPosition(sf::Vector2f(startPosX + 250 * i, startPosY));
	}

	//factUnlock **************************************************************************************
	doc.LoadFile("Resources/Data/FactUnlock.xml");
	tinyxml2::XMLElement *secti = doc.FirstChildElement("Section");

	while(secti != 0){
		const tinyxml2::XMLElement *unlock = secti->FirstChildElement();
		if(secti->IntAttribute("level") == section){
			while(unlock != 0){
				mUnlockVector.push_back(unlock->GetText());
				unlock = unlock->NextSiblingElement();
			}
			break;
		}
		secti = secti->NextSiblingElement();
	}

	saveUnlocked();
}

AchievementState::~AchievementState(){
	
	//tror ej detta behövs
	mAnimalVector.clear();
	mImageVector.clear();
}

void AchievementState::update(){

	if(mAnimalVector.empty()){
		EventManager::getInst().addEvent("popState");
	}

	ParticleManager::getInst().update();

	mButton->update();

}

void AchievementState::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mPreState->render();

	if(!mAnimalVector.empty()){
		window->draw(mSprite);
		window->draw(mButton->getSprite());

		for(ImageVector::iterator i = mImageVector.begin(); i != mImageVector.end(); i++){
			window->draw(*(*i));
		}
	}

	//ta bort sen, funkar inte atm
	ParticleManager::getInst().render(*window);

}



std::string AchievementState::getMusic(){

	return mMusic;
}

void AchievementState::saveUnlocked(){
	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

	tinyxml2::XMLElement *elm = doc.FirstChildElement();


	while(elm != 0){
		for(UnlockVector::iterator i = mUnlockVector.begin(); i != mUnlockVector.end(); i++){
			if((*i) == elm->Name()){
				elm->SetAttribute("newFacts", 1);
				elm->SetAttribute("unlocked", 1);
			}
		}
		elm = elm->NextSiblingElement();
	}

	doc.SaveFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

}