#include "Spot.h"
#include "ResourceManager.h"



Spot::Spot(int level, sf::Vector2f position):
	mLevel(level),
	mPlacedAnimal(0),
	mActSpot(false)
{
	ResourceManager* r = &ResourceManager::getInst();

	mTexture = *r->getTexture("spot2.png");

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
	if(mActSpot){
		mRect.left = mRect.width/3;//<-------------------statiska siffor
		mSprite->setTextureRect(mRect);
	}else {
		mRect.left = 0; //<-------------------statiska siffor
		mSprite->setTextureRect(mRect);
	}

	if(mPlacedAnimal != 0){
		mRect.left = mRect.width/3*2;
		mSprite->setTextureRect(mRect);
	}
}

int Spot::getLevel(){
	return mLevel;
}

sf::Sprite* Spot::getSprite(){
	return mSprite;
}

AnimalPrototype* Spot::getPlacedAnimal(){
	return mPlacedAnimal;
}

//används nog inte
void Spot::setPlacedAnimal(AnimalPrototype* prototype){
	mPlacedAnimal = prototype;
}

bool Spot::getActSpot(){
	return mActSpot;
}