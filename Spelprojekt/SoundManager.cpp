#include "SoundManager.h"
#include "tinyxml2.h"
#include "ResourceManager.h"

SoundManager::SoundManager()
	: mMuted(false)
	, mMusicVolume(100)
	, mCurrentMusic(0)
	, mFading(false)
	, mSoundVolume(100)
	, mCurrentVoice(0)
	, mVoiceVolume(100){

		tinyxml2::XMLDocument doc;
		doc.LoadFile("Resources/data/settings.xml");

		tinyxml2::XMLElement* elm = doc.FirstChildElement("Sound");

		mMusicVolume = elm->FloatAttribute("musicVolume");
		mSoundVolume = elm->FloatAttribute("soundVolume"); 
		mVoiceVolume = elm->FloatAttribute("voiceVolume"); 
		mMuted = elm->BoolAttribute("muted");


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

	if(mCurrentVoice != 0){
		if(mCurrentVoice->getStatus() == sf::Sound::Stopped){
			delete mCurrentVoice;
			mCurrentVoice = 0;
		}
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

sf::Time& SoundManager::playVoice(std::string filename){
	//vi kanske får ladda in alla dessa vid cutscenes start för att undvika avbrott
	if(mCurrentVoice != 0){
		mCurrentVoice->stop();
		delete mCurrentVoice;
	}
	mCurrentVoice = new sf::Music();
	mCurrentVoice->openFromFile(filename);
	//mCurrentVoice->setBuffer(*ResourceManager::getInst().getSoundBuffer(filename));
	mCurrentVoice->setVolume(mVoiceVolume * (!mMuted));
	mCurrentVoice->play();
	return mCurrentVoice->getDuration();
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

void SoundManager::setMusicVolume(float volume){
	if(mCurrentMusic != 0){
		mCurrentMusic->setVolume(volume*(!mMuted));
		mMusicVolume = volume;
	}
}

void SoundManager::setSoundVolume(float volume){
	mSoundVolume = volume * (!mMuted);
}

void SoundManager::setMuted(bool muted){
	mMuted = muted;
	setSoundVolume(mSoundVolume);
	setMusicVolume(mMusicVolume);
}