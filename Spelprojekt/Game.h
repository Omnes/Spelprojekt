#ifndef GAME
#define GAME
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Clock.hpp>

class Game{
public:

	Game();
	void run();
	static float elipsedTime;
	void countFrames();
	std::string setStringStream(int frames);
	void drawFPS(sf::RenderWindow* window);
	void PollWindowEvents(sf::RenderWindow* window);

private:

	int mFrames, mCurrentFPS;
	sf::Clock mClock;
	bool mInFocus;
};



#endif