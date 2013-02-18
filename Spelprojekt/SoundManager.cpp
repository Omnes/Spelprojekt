#include "SoundManager.h"

SoundManager::SoundManager():mMuted(false), mVolume(100), mCurrentMusic(0), mFading(false){

}

SoundManager::~SoundManager(){}

SoundManager& SoundManager::getInst(){
	static SoundManager instance;
	return instance;
}

float clampValue(float value){
	if(value < 0){
		value = 0;
	}
	if(value > 100){
		value = 100;
	}

	return value;

}

void SoundManager::update(){
	if(mFading){
		if(mCurrentMusic->getVolume()>0){
			mCurrentMusic->setVolume(clampValue(mCurrentMusic->getVolume() - mFadeVolumeDeltaChange));
			mFadeToMusic->setVolume(clampValue(mVolume - mCurrentMusic->getVolume()));
		}else{
			mFading = false;
			mCurrentMusic->stop();
			delete mCurrentMusic;
			mCurrentMusic = mFadeToMusic;
			mFadeToMusic = 0;
		}
	}
}


void SoundManager::play(std::string filePath){
	if(mCurrentMusic != 0){
		mCurrentMusic->stop();
		delete mCurrentMusic;
		mCurrentMusic = 0;
	}

	//kanske ska ha en fade här?
	mCurrentMusic = new sf::Music;
	mCurrentMusic->openFromFile(filePath);
	mCurrentMusic->setVolume(mVolume * (!mMuted));
	mCurrentMusic->setLoop(true);
	mCurrentMusic->play();
	
}

void SoundManager::fadeTo(std::string filePath,float fadeTime){
	float currentVolume; 

	if(mCurrentMusic !=0){
		currentVolume = mCurrentMusic->getVolume();
	}else{
		currentVolume = 0;
	}

	mFadeVolumeDeltaChange = currentVolume/fadeTime;

	mFadeToMusic = new sf::Music;
	mFadeToMusic->openFromFile(filePath);
	mFadeToMusic->setVolume(0);
	mFadeToMusic->setLoop(true);
	mFadeToMusic->play();

	mFading = true;
}