#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include <string>
#include "MusicLoop.h"
#include <SFML\Audio\Sound.hpp>

class SoundManager{
public:
	
	static SoundManager& getInst();
	void update();

	void loadSettings();

	void play(std::string filename);
	void play(sf::Sound& sound);
	sf::Time& playVoice(std::string filename);
	void fadeTo(std::string filename,float fadeTime);
	MusicLoop* getCurrentPlaying();
	void setMusicVolume(float volume);
	void setSoundVolume(float volume);
	void setMuted(bool muted);

private:
	float mMusicVolume;
	float mVoiceVolume;
	float mSoundVolume;
	bool mMuted;
	sf::Sound* mCurrentVoice;

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