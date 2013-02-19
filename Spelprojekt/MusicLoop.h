#ifndef MUSICLOOP
#define MUSICLOOP

#include <SFML\Audio\Music.hpp>
#include <SFML\System\Clock.hpp>
#include <string>

class MusicLoop{
public:
	MusicLoop(std::string filename);
	~MusicLoop();

	void update();
	void play();
	void setVolume(float volume);
	float getVolume();
	void stop();
	std::string getFilepath();


private:
	sf::Clock mMusicTimer;
	std::string mFileName;
	sf::Music mFirstFile;
	sf::Music mSecondFile;
	sf::Music* mCurrentPlaying;
	float mVolume;
};

#endif