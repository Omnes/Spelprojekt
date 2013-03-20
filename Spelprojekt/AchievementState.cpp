#include "AchievementState.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "SoundManager.h"
#include "StateManager.h"


AchievementState::AchievementState(int section) :
	mSection(section)
{

	mPreState = StateManager::getInst().getTop();
	mMusic = mPreState->getMusic();

	mSprite.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/AchievementMenu/unlock.png"));
	mSprite.setPosition(50,50);

	sf::Vector2f buttonPos = sf::Vector2f(mSprite.getTexture()->getSize().x/2, mSprite.getTexture()->getSize().y - 200);

	mButton = new Button(sf::Vector2f(buttonPos.x - 125, buttonPos.y), "popState", "Resources/Menu/AchievementMenu/okejknapp.png", "sound");

	//läser in sprites till achievementstate-skärm
	readSprites();

	int startPosX = 350;
	int startPosY = 350;

	//kanske onödig
	for(std::vector<sf::Sprite*>::size_type i = 0; i < mImageVector.size(); i++){
		mImageVector[i]->setPosition(sf::Vector2f(startPosX + 250 * i, startPosY));
	}

	readUnlocked();
	saveUnlocked();
	readSaveExtraFact();
}

//
AchievementState::~AchievementState(){
	while(!mImageVector.empty()){
		delete mImageVector.back();
		mImageVector.pop_back();
	}
}

//
void AchievementState::update(){

	if(mAnimalVector.empty()){
		EventManager::getInst().addEvent("popState");
	}

	ParticleManager::getInst().update();

	mButton->update();

}

//
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

//läser sprites till achievementstate-skärm
void AchievementState::readSprites(){
	mDoc.LoadFile("Resources/Data/AnimalUnlock.xml");
	tinyxml2::XMLElement *sect = mDoc.FirstChildElement("Section");

	while(sect != 0){
		const tinyxml2::XMLElement *animal = sect->FirstChildElement();
		if(sect->IntAttribute("level") == mSection){
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
		mDoc.LoadFile((*i).c_str());

		tinyxml2::XMLElement *elm = mDoc.FirstChildElement("Animal")->FirstChildElement("Images");
		tinyxml2::XMLElement *elmf = mDoc.FirstChildElement("Animal")->FirstChildElement("ImageAttr");

		tinyxml2::XMLElement *name = mDoc.FirstChildElement()->FirstChildElement("Name");

		sf::Texture* tex = resourceManager->getTexture(elm->GetText());
		sf::Sprite *sprite = new sf::Sprite();
		sprite->setTexture(*tex);
		sprite->setTextureRect(sf::IntRect(0,0, tex->getSize().x/elmf->IntAttribute("frames"), tex->getSize().y/2));

		mImageVector.push_back(sprite);
	}
}

//läser in fakta under levlarna
void AchievementState::readUnlocked(){
	//factUnlock **************************************************************************************
	mDoc.LoadFile("Resources/Data/FactUnlock.xml");
	tinyxml2::XMLElement *secti = mDoc.FirstChildElement("Section");

	while(secti != 0){
		const tinyxml2::XMLElement *unlock = secti->FirstChildElement("Fact");
		if(secti->IntAttribute("level") == mSection){
			while(unlock != 0){
				mUnlockVector.push_back(unlock->GetText());
				unlock = unlock->NextSiblingElement();
			}
			break;
		}
		secti = secti->NextSiblingElement();
	}
}


//spara unlocked för varje level
void AchievementState::saveUnlocked(){
	mDoc.LoadFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

	tinyxml2::XMLElement *elm = mDoc.FirstChildElement();


	while(elm != 0){
		for(UnlockVector::iterator i = mUnlockVector.begin(); i != mUnlockVector.end(); i++){
			if((*i) == elm->Name()){
				elm->SetAttribute("newFacts", 1);
				elm->SetAttribute("unlocked", 1);
			}
		}
		elm = elm->NextSiblingElement();
	}

	mDoc.SaveFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

}

//extraFact
void AchievementState::readSaveExtraFact(){

	//onödigt och kass
	//inläsning av section från FactUnlock
	mDoc.LoadFile("Resources/Data/FactUnlock.xml");
	tinyxml2::XMLElement *secti = mDoc.FirstChildElement("Section");

	std::vector<std::string> extraVector;

	while(secti != 0){
		const tinyxml2::XMLElement *unlock = secti->FirstChildElement("ExtraFact");
		if(secti->IntAttribute("level") == mSection){
			while(unlock != 0){
				extraVector.push_back(unlock->GetText());
				unlock = unlock->NextSiblingElement();
			}
			break;
		}
		secti = secti->NextSiblingElement();
	}

	//spara i UnlockedFacts ''''''''''''''''''''''''''''''''''''''''''''''''''''''
	mDoc.LoadFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

	tinyxml2::XMLElement *elm = mDoc.FirstChildElement();

	while(elm != 0){
		for(std::vector<std::string>::iterator i = extraVector.begin(); i != extraVector.end(); i++){
			if((*i) == elm->Name()){
				elm->SetAttribute("extraUnlocked", 1);
			}
		}
		elm = elm->NextSiblingElement();
	}

	mDoc.SaveFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

}