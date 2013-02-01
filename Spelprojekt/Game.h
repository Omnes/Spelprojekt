#ifndef GAME
#define GAME
#include <SFML\Graphics\Text.hpp>
#include <SFML\System\Clock.hpp>

class Game{
public:

	Game();
	void run();
	static float elipsedTime;
	void countFrames();
	std::string setStringStream(int frames);

private:

	int mFrames, mCurrentFPS;
	sf::Clock mClock;
};



#endif