#include "MusicLoop.h"

MusicLoop::MusicLoop(std::string filename):mCurrentPlaying(0), mVolume(100){
	mFirstFile.openFromFile(filename+"1.ogg");
	mSecondFile.openFromFile(filename+"2.ogg");
	mFileName = filename;
	mMusicTimer.restart();
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
			mCurrentPlaying->stop();
			mMusicTimer.restart();
			mSecondFile.play();
			mCurrentPlaying = &mSecondFile;
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
	//if(mCurrentPlaying != 0){ kanske crashar nu
		mCurrentPlaying->stop();
	//}

}

std::string MusicLoop::getFilepath(){
	return mFileName;
}