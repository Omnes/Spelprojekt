#include "Particle.h"
#include "Behavior.h"


Particle::Particle(){
	mLife = -10;
	mBehavior = 0;
}


Particle::~Particle(){
}

void Particle::update(){
	mLife --;
	mSpeed += mSpeedIncrease;
	mPosition += (mDirection * mSpeed);
	mRotation += mRotationIncrease;
	mScale += mScaleIncrease;


	mColorR += mColorChangeR;
	mColorG += mColorChangeG;
	mColorB += mColorChangeB;
	mColorA += mColorChangeA;

	if(!mBehavior == 0){
		mBehavior->update(this);
	}


	mSprite.setColor(sf::Color(mColorR, mColorG, mColorB, mColorA));
	mSprite.setPosition(mPosition);
	mSprite.setRotation(mRotation);
	mSprite.setScale(sf::Vector2f(mScale, mScale));

}

const sf::Sprite& Particle::getSprite()const{
	return mSprite;
}
