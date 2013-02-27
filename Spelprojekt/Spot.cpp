#include "Spot.h"
#include "ResourceManager.h"



Spot::Spot(int level, sf::Vector2f position):
	mLevel(level),
	mPlacedAnimal(0),
	mActSpot(false),
	//mTaken(false),
	mColor(0,0,0,0),
	mExtraSpeed(false)
{
	ResourceManager* r = &ResourceManager::getInst();

	mTexture = *r->getTexture("Resources/Menu/TacticMenu/spot.png");

	mSprite = new sf::Sprite;
	mSprite->setTexture(mTexture);
	mSprite->setPosition(position);
	
	mSprite->setOrigin(mTexture.getSize().x/2, mTexture.getSize().y/2); // kom ihåg att fixa orgin när vi fått grafik
	mSprite->setColor(sf::Color(0,0,0,0));
}

Spot::~Spot(){}

//ett djur kan placeras här
void Spot::setActSpot(bool dragAnimal){
	mActSpot = dragAnimal;
}

//returnerar om ett djur kan sitta här
bool Spot::getActSpot(){
	return mActSpot;
}

//returnerear vilken nivå denna spot är på
int Spot::getLevel(){
	return mLevel;
}

void Spot::update(){
	if(mPlacedAnimal != 0 || mActSpot){
		mSprite->setColor(mColor);
	}else{
		mSprite->setColor(sf::Color(0.0f,0.0f,0.0f,0.0f));
	}
}

sf::Sprite* Spot::getSprite(){
	return mSprite;
}

void Spot::setColorSpot(sf::Color color){

	mColor = color;

	mSprite->setColor(mColor);
}

sf::Color Spot::getColorSpot(){
	return mColor;
}

void Spot::setPrototypeAnimal(AnimalPrototype* PlacedAnimal){
	mPlacedAnimal = PlacedAnimal;
}

AnimalPrototype* Spot::getPrototypeAnimal(){
	return mPlacedAnimal;
}

void Spot::setAfraidAnimal(bool extraSpeed){
	mExtraSpeed = extraSpeed;
}

bool Spot::getAfraidAnimal(){
	return mExtraSpeed;
}

void Spot::setOriginalColor(sf::Color originalColor){
	mOriginalColor = originalColor;
}

void Spot::resetColor(){
	mColor = mOriginalColor;
}