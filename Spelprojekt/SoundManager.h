#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include <string>
#include <SFML\Audio\Music.hpp>

class SoundManager{
public:
	
	static SoundManager& getInst();
	void update();

	void play(std::string filePath);
	void fadeTo(std::string filePath,float fadeTime);

private:
	float mVolume;
	bool mMuted;
	sf::Music* mCurrentMusic;
	sf::Music* mFadeToMusic;

	bool mFading;

	float mFadeVolumeDeltaChange;

	SoundManager();
	~SoundManager();
	SoundManager& operator=(const SoundManager&);
	SoundManager(const SoundManager&);



};






#endif