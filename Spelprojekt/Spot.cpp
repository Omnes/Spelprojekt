#include "Spot.h"
#include "ResourceManager.h"


Spot::Spot(int level):
	mLevel(level)
{
	mTexture = ResourceManager::getInst().getTexture("spot.png");
	mSprite->setTexture(*mTexture);
//	mSprite->setPosition(position);
	
	mRect = sf::IntRect(0,0, mTexture->getSize().x/2, mTexture->getSize().y);
	mSprite->setTextureRect(mRect);
}

Spot::~Spot(){}


void Spot::activateSpot(bool dragAnimal){
	if(dragAnimal){
		mRect.left = mRect.width;//<-------------------statiska siffor
		mSprite->setTextureRect(mRect);
	}else{
		mRect.left = 0; //<-------------------statiska siffor
		mSprite->setTextureRect(mRect);
	}
}

int Spot::getLevel(){
	return mLevel;
}

sf::Sprite* Spot::getSprite(){
	return mSprite;
}
