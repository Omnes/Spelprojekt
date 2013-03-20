#include "OptionSlider.h"

OptionSlider::OptionSlider(sf::Vector2f posBg, std::string element, std::string attribute) : 
	mElement(element),
	mPressed(false),
	mAttribute(attribute),
	mTex(ResourceManager::getInst().getTexture("Resources/Menu/OptionsMenu/arrowslider.png")),
	mSprite(*mTex)
{
	mTex = ResourceManager::getInst().getTexture("Resources/Menu/OptionsMenu/Slider.png");
	mSpriteBg.setTexture(*mTex);
	mSpriteBg.setPosition(posBg);
	mMinPos = mSpriteBg.getPosition().x;
	mMaxPos = mSpriteBg.getTexture()->getSize().x + mSpriteBg.getPosition().x;
	
	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Settings.xml");

	mVolume = doc.FirstChildElement(element.c_str())->IntAttribute(attribute.c_str());

	mPosRatio = mSpriteBg.getTexture()->getSize().x / 100.0f;

	mSprite.setPosition((mVolume * mPosRatio) + mMinPos, mSpriteBg.getPosition().y + 24);

	mVolRatio = 100.0f / mSpriteBg.getTexture()->getSize().x;

	mSprite.setOrigin(mSprite.getTexture()->getSize().x/2, mSprite.getTexture()->getSize().y/2);
}

OptionSlider::~OptionSlider(){}

void OptionSlider::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->draw(mSpriteBg);
	window->draw(mSprite);

}

void OptionSlider::update(){

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());

	if(mSprite.getGlobalBounds().contains(mousePosition)){
		mPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}

	if(mPressed){
		mSprite.setPosition(mousePosition.x, mSprite.getPosition().y);
		clamPos();
		mVolume = (mSprite.getPosition().x - mMinPos) * mVolRatio;
		//sätter volym
		//SoundManager::getInst().setMusicVolume(mVolume);
	}

	if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		mPressed = false;
	}
}

void OptionSlider::saveSettings(){

	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Settings.xml");

	doc.FirstChildElement(mElement.c_str())->SetAttribute(mAttribute.c_str(), mVolume);

	doc.SaveFile("Resources/Data/Settings.xml");

}

void OptionSlider::clamPos(){
	if(mSprite.getPosition().x < mMinPos){
		mSprite.setPosition(mMinPos, mSprite.getPosition().y);
	}else if(mSprite.getPosition().x > mMaxPos){
		mSprite.setPosition(mMaxPos, mSprite.getPosition().y);
	}
}