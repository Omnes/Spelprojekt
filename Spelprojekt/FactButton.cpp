#include "FactButton.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "WindowManager.h"
#include "LevelManager.h"

FactButton::FactButton(sf::Vector2f pos, std::string evt, std::string img, std::string sound) 
	: mPosition(pos)
	, mEvent(evt)
	, mCurrentImage(0)
	, mSmokeSystem("SlowSpark",110)
	, mTimer(0)
	, mNewFact(false)
{

	mTexture = *(ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(mTexture);
	mSprite.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture.getSize().x/4, mTexture.getSize().y); //Rekten ska ha rätt bredd
	mSprite.setTextureRect(mRectangle);


	mSmokeSystem.setBlendMode(sf::BlendAdd);
	mEmitter.setPosition(mPosition);

}

FactButton::~FactButton(){
}

void FactButton::update(){

	mTimer++;

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

	//mAlive står här. ändra om du behöver
	if(mSprite.getGlobalBounds().contains(mousePosition)){		
	
		mCurrentImage=1;

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && GlobalButtonTimer::onCoolDown()){ 
			
			
				mCurrentImage=2;
				EventManager::getInst().addEvent(mEvent);

				GlobalButtonTimer::globalRestart();
		}		
	}else{
		mCurrentImage = 0;
	}
	
	if(mNewFact){
		mEmitter.burst(mSmokeSystem,sf::FloatRect(0,0,mSprite.getLocalBounds().width,mSprite.getLocalBounds().height),1);
	}

	if(mTimer > 90){
		mNewFact = readFile();
		mTimer = 0;
	}


	mRectangle.left = mRectangle.width*mCurrentImage; // kommentera in den här när vi har en lämplig bild
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& FactButton::getSprite(){
	return mSprite;
}

bool FactButton::readFile(){

	bool newFact = false;

	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Animalipedia/UnlockedFacts.xml");

	tinyxml2::XMLElement *elm = doc.FirstChildElement();

	while(elm != 0){
		if(elm->BoolAttribute("newFacts")){
			newFact = true;
		}
		elm = elm->NextSiblingElement();
	}

	return newFact;
}