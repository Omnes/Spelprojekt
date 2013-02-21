#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include <string>
#include "MusicLoop.h"
#include <SFML\Audio\Sound.hpp>

class SoundManager{
public:
	
	static SoundManager& getInst();
	void update();

	void play(std::string filename);
	void play(sf::Sound& sound);
	void fadeTo(std::string filename,float fadeTime);
	MusicLoop* getCurrentPlaying();

private:
	float mMusicVolume;
	float mSoundVolume;
	bool mMuted;
	MusicLoop* mCurrentMusic;
	MusicLoop* mFadeToMusic;

	bool mFading;

	float mFadeVolumeDeltaChange;

	SoundManager();
	~SoundManager();
	SoundManager& operator=(const SoundManager&);
	SoundManager(const SoundManager&);



};






#endif