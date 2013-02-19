#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include <string>
#include "MusicLoop.h"

class SoundManager{
public:
	
	static SoundManager& getInst();
	void update();

	void play(std::string filename);
	void fadeTo(std::string filename,float fadeTime);
	void loop();
	MusicLoop* getCurrentPlaying();

private:
	float mVolume;
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