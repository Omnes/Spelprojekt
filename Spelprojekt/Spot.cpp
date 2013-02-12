#include "Spot.h"
#include "ResourceManager.h"



Spot::Spot(int level, sf::Vector2f position):
	mLevel(level),
	mPlacedAnimal(0),
	mActSpot(false),
	mTaken(false)
{
	ResourceManager* r = &ResourceManager::getInst();

	mTexture = *r->getTexture("Resources/Menu/TacticMenu/spot2.png");

	mSprite = new sf::Sprite;
	mSprite->setTexture(mTexture);
	mSprite->setPosition(position);
	
	mRect = sf::IntRect(0,0, mTexture.getSize().x/2, mTexture.getSize().y);
	mSprite->setTextureRect(mRect);
	mSprite->setOrigin(64,64); // kom ihåg att fixa orgin när vi fått grafik

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

void Spot::setColorSpot(bool colorGreen){

	if(colorGreen){
		mRect.left = mRect.width/3;//<-------------------statiska siffor
		mSprite->setTextureRect(mRect);
	}else{
		mRect.left = 0; //<-------------------statiska siffor
		mSprite->setTextureRect(mRect);
	}

}