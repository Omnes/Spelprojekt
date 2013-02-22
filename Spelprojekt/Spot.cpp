#include "Spot.h"
#include "ResourceManager.h"



Spot::Spot(int level, sf::Vector2f position):
	mLevel(level),
	mPlacedAnimal(0),
	mActSpot(false),
	mTaken(false),
	mColor(0)
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


void Spot::setActSpot(bool dragAnimal){
	mActSpot = dragAnimal;
}

int Spot::getLevel(){
	return mLevel;
}

sf::Sprite* Spot::getSprite(){
	return mSprite;
}

bool Spot::getActSpot(){
	return mActSpot;
}

void Spot::setTakenSpot(bool taken){
	mTaken = taken;
}

bool Spot::getTakenSpot(){
	return mTaken;
}

//byt namn till typ. chan
void Spot::setColorSpot(int colorGreen){

	mColor = colorGreen;

	//kanske ändra sen. fulkod. 
	if(colorGreen == 1/*uptagen men ej snabbast*/){
		mSprite->setColor(sf::Color(255,255,255,255));
	}else if(colorGreen == 2/*uptagen och snabbast*/){
		mSprite->setColor(sf::Color(255,200,255,255));
	}else{
		mSprite->setColor(sf::Color(0,0,0,0));
	}

}

void Spot::setPrototypeAnimal(AnimalPrototype* PlacedAnimal){
	mPlacedAnimal = PlacedAnimal;
}

AnimalPrototype* Spot::getPrototypeAnimal(){
	return mPlacedAnimal;
}

int Spot::getColorSpot(){
	return mColor;
}