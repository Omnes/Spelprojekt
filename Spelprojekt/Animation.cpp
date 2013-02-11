#include "Animation.h"

Animation::Animation(sf::Texture *texture, int frametime, int frames): mTexture(texture), mFrametime(frametime), mFrames(frames), mCurrentframe(0), mCurrentanimation(0){

	mSprite.setTexture(*mTexture);
	mRectangle = sf::IntRect(0,0,mTexture->getSize().x/mFrames,mTexture->getSize().y/2);
	mSprite.setTextureRect(mRectangle);
	setCurrentAnimation(1);

}

Animation::~Animation(){

}

void Animation::update(){

	if(mTimer.getElapsedTime().asMilliseconds() > mFrametime){
		
		mCurrentframe+=1;
		mTimer.restart();
	}

	if(mCurrentframe > mFrames-1){
		
		mCurrentframe=0;
	}

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
