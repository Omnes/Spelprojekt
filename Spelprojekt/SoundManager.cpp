#include "SoundManager.h"
#include "tinyxml2.h"

SoundManager::SoundManager()
	: mMuted(false)
	, mMusicVolume(100)
	, mCurrentMusic(0)
	, mFading(false)
	, mSoundVolume(100){

		tinyxml2::XMLDocument doc;
		doc.LoadFile("Resources/data/settings.xml");

		const tinyxml2::XMLAttribute* attr = doc.FirstChildElement("Sound")->FirstAttribute();

		mMusicVolume = attr->FloatValue();
		attr = attr->Next();
		mSoundVolume = attr->FloatValue(); 
		attr = attr->Next();
		mMuted = attr->BoolValue();


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
		}else{
			mFading = false;
			mCurrentMusic->stop();
			delete mCurrentMusic;
			mCurrentMusic = mFadeToMusic;
			mCurrentMusic->play();
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
	mCurrentMusic->setVolume(mMusicVolume * (!mMuted));
	mCurrentMusic->play();
	
}

void SoundManager::play(sf::Sound &sound){
	sound.setVolume(mSoundVolume * (!mMuted));
	sound.play();
}

void SoundManager::fadeTo(std::string filename,float fadeTime){
	float currentVolume; 

	if(mCurrentMusic !=0){
		currentVolume = mCurrentMusic->getVolume();
		if(filename == mCurrentMusic->getFilepath()){
			return;
		}
	}else{
		currentVolume = 0;
	}

	mFadeVolumeDeltaChange = currentVolume/fadeTime;

	if(mFadeToMusic != 0 && mCurrentMusic != 0){
		mCurrentMusic->stop();
		delete mCurrentMusic;
		mCurrentMusic = mFadeToMusic;
		mFadeToMusic = 0;
		mCurrentMusic->setVolume(mMusicVolume*(!mMuted));
	}

	mFadeToMusic = new MusicLoop(filename);
	mFadeToMusic->setVolume(mMusicVolume*(!mMuted));

	mFading = true;
}

MusicLoop* SoundManager::getCurrentPlaying(){
	return mCurrentMusic;
}