#include "MusicLoop.h"
#include <iostream>

MusicLoop::MusicLoop(std::string filename):mCurrentPlaying(0), mVolume(100){
	mFirstFile.openFromFile(filename+"1.ogg");
	mSecondFile.openFromFile(filename+"2.ogg");
	mFileName = filename;
	mMusicTimer.restart();
	mSecondFile.play();
	mSecondFile.setVolume(0);

	mSecondFile.setLoop(true);

}


MusicLoop::~MusicLoop(){}


void MusicLoop::play(){
	mMusicTimer.restart();
	mFirstFile.play();
	mCurrentPlaying = &mFirstFile;


}


void MusicLoop::update(){

	if(mCurrentPlaying != 0){
		if(mCurrentPlaying->getDuration() < mMusicTimer.getElapsedTime() && mCurrentPlaying->getStatus() == sf::Music::Playing){
			if(mCurrentPlaying != &mSecondFile){
				mCurrentPlaying->stop();
				mSecondFile.setVolume(mVolume);
				mSecondFile.play();
				mCurrentPlaying = &mSecondFile;
			}
			std::cout << mFileName << " has looped at " << mMusicTimer.getElapsedTime().asSeconds() << " (" <<mMusicTimer.getElapsedTime().asMilliseconds() << ")" << std::endl;
			mMusicTimer.restart();
		}
	}
}


void MusicLoop::setVolume(float volume){
	mVolume = volume;
	mFirstFile.setVolume(volume);
	mSecondFile.setVolume(volume);
}

float MusicLoop::getVolume(){
	return mVolume;
}


void MusicLoop::stop(){
	if(mCurrentPlaying != 0){
		mCurrentPlaying->stop();
	}

}

std::string MusicLoop::getFilepath(){
	return mFileName;
}