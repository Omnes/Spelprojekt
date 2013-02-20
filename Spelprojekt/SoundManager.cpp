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
	if(mCurrentMusic != 0){
		mCurrentMusic->update();
	}

}


void SoundManager::play(std::string filename){
	if(mCurrentMusic != 0){
		mCurrentMusic->stop();
		delete mCurrentMusic;
		mCurrentMusic = 0;
	}

	//kanske ska ha en fade här?
	mCurrentMusic = new MusicLoop(filename);
	mCurrentMusic->setVolume(mVolume * (!mMuted));
	mCurrentMusic->play();
	
}

void SoundManager::fadeTo(std::string filename,float fadeTime){
	float currentVolume; 

	if(mCurrentMusic !=0){
		currentVolume = mCurrentMusic->getVolume();
	}else{
		currentVolume = 0;
	}

	mFadeVolumeDeltaChange = currentVolume/fadeTime;

	if(mFadeToMusic != 0 && mCurrentMusic != 0){
		mCurrentMusic->stop();
		delete mCurrentMusic;
		mCurrentMusic = mFadeToMusic;
		mFadeToMusic = 0;
		mCurrentMusic->setVolume(mVolume*(!mMuted));
	}

	mFadeToMusic = new MusicLoop(filename);
	mFadeToMusic->setVolume(0);
	mFadeToMusic->play();

	mFading = true;
}

void SoundManager::loop(){


}

MusicLoop* SoundManager::getCurrentPlaying(){
	return mCurrentMusic;
}