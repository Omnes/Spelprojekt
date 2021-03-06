#include "Animation.h"

Animation::Animation(sf::Texture *texture, int frametime, int xframes, int yframes)
	: mTexture(texture)
	, mFrametime(frametime)
	, mOriginalFrameTime(frametime)
	, mFrames(xframes)
	, mCurrentframe(0)
	, mCurrentanimation(0){

	mSprite.setTexture(*mTexture);
	mRectangle = sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y/yframes);
	mSprite.setTextureRect(mRectangle);
	mSprite.setOrigin(mTexture->getSize().x/(xframes*2),mTexture->getSize().y/(yframes*2));
	setCurrentAnimation(0);
	mHasPlayed = false;

}

Animation::~Animation(){

}

void Animation::update(){

	if(mTimer.getElapsedTime().asMilliseconds() > mFrametime && mFrametime != 0){
		
		mCurrentframe+=1;
		mTimer.restart();
	}

	if(mCurrentframe > mFrames-1){
		
		mCurrentframe=0;
		mHasPlayed = true;
	}

	//mSprite.rotate((rand()%2) - 1);
	//mSprite.setScale(0.5 + std::sin((double)mTimer.getElapsedTime().asSeconds())*3,0.5 + std::sin((double)mTimer.getElapsedTime().asSeconds())*3);

	mRectangle.left = mRectangle.width*mCurrentframe;
	mSprite.setTextureRect(mRectangle);
}

void Animation::setCurrentAnimation(int animation){

	mRectangle.top = mRectangle.height*animation;
}

sf::Sprite* Animation::getSprite(){

	return &mSprite;
}

void Animation::setPosition(sf::Vector2f position){

	mSprite.setPosition(position);
}

void Animation::setFrameTime(float value){
	mFrametime = mOriginalFrameTime/value;
}

bool Animation::getHasPlayed(){
	return mHasPlayed;
}
