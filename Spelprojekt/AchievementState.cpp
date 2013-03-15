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


		sf::Texture* tex = resourceManager->getTexture(elm->GetText());
		sf::Sprite *sprite = new sf::Sprite();
		sprite->setTexture(*tex);
		sprite->setTextureRect(sf::IntRect(0,0, tex->getSize().x/elmf->IntAttribute("frames"), tex->getSize().y/2));
		mImageVector.push_back(sprite);
	}


	//mTutorialDuration = 10.0f;
	//mTimer.restart();
}

AchievementState::~AchievementState(){}

void AchievementState::update(){

	mButton->update();

}

void AchievementState::render(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	mPreState->render();
	window->draw(mSprite);
	window->draw(mButton->getSprite());

	for(ImageVector::iterator i = mImageVector.begin(); i != mImageVector.end(); i++){
		window->draw(*(*i));
	}

}



std::string AchievementState::getMusic(){

	return mMusic;
}
