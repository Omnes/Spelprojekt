#ifndef COUNTDOWN
#define COUNTDOWN
#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>



class Countdown: public States{
public:
	Countdown();
	~Countdown();

	void render();
	void update();

	std::string getMusic();


private:

	sf::Clock mCountdown;
	sf::Clock mAnimationTimer;
	States* mRenderState;
	sf::Sprite mSprite;
	std::string mMusic;
	sf::IntRect mRect;
	int mCurrentNumber;
};

#endif