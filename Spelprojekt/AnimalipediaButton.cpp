#include "AnimalipediaButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "Animalipedia.h"
#include "FontMaster.h"
#include "tinyxml2.h"
#include "SoundManager.h"


AnimalipediaButton::AnimalipediaButton(sf::Vector2f pos, std::string page, std::string title, std::string sound, Animalipedia* wiki) 
	: mPosition(pos)
	, mCurrentImage(0)
	, mInfo(page)
	, mTitle(title)
	, mWiki(wiki)
	, mNewEffekt("SlowSpark",30){
	mTexture = (ResourceManager::getInst().getTexture("Resources/Menu/Animalipedia/text_knapp.png"));
	mSprite.setTexture(*mTexture);
	setPosition(mPosition);

	mTitle.setFont(FontMaster::sFont);
	mTitle.setCharacterSize(24);
	mTitle.setPosition(mPosition);
	mTitle.setColor(sf::Color(0,0,0));
	mRectangle = sf::IntRect(0,0, mTexture->getSize().x/4, mTexture->getSize().y);
	mSprite.setTextureRect(mRectangle);
	mSoundBuffer = (ResourceManager::getInst().getSoundBuffer(sound));
	mSound.setBuffer(*mSoundBuffer);



}

AnimalipediaButton::~AnimalipediaButton(){

}


void AnimalipediaButton::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

	if(mNewInfo && mLocked){
		mEmitter.burst(mNewEffekt,sf::FloatRect(0,0,mSprite.getTextureRect().width,mSprite.getTextureRect().height),1);
	}
	
	if(mSprite.getGlobalBounds().contains(mousePosition) && mLocked > 0){		
	
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mWiki->getInfo() != mInfo ){ 
			mCurrentImage=2;
			SoundManager::getInst().play(mSound);
			if(mNewInfo){
				tinyxml2::XMLDocument doc;
				doc.LoadFile("Resources/Data/Animalipedia/UnlockedFacts.xml");
				doc.FirstChildElement(mInfo.c_str())->SetAttribute("newFacts",0);
				doc.SaveFile("Resources/Data/Animalipedia/UnlockedFacts.xml");
			}
			mNewInfo = false;
			mWiki->setInfo(mInfo);
		}		
	}

	else{

		mCurrentImage=0;
	}

	if(mWiki->getInfo() == mInfo){
		mCurrentImage = 2;	
	}

	if(mLocked == 0){
		mCurrentImage = 3;
	}

	mRectangle.left = mRectangle.width*mCurrentImage;
	mSprite.setTextureRect(mRectangle);
}

void AnimalipediaButton::render(){

	sf::RenderWindow *window = WindowManager::getInst().getWindow();

	window->draw(mSprite);
	window->draw(mTitle);
}

void AnimalipediaButton::setLocked(int level){
	mLocked = level;
}

void AnimalipediaButton::setNewInfo(bool boolean){
	mNewInfo = boolean;
}

void AnimalipediaButton::setPosition(sf::Vector2f pos){
	mPosition = pos;
	mSprite.setPosition(mPosition);
	mTitle.setPosition(mPosition+sf::Vector2f(40,8));
	mEmitter.setPosition(mPosition);
}