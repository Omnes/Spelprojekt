#ifndef GAMEOVER
#define GAMEOVER

#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Button.h"
#include <SFML\Graphics\Text.hpp>


class GameOver: public States{
public:
	GameOver();
	~GameOver();
	virtual void update();
	virtual void render();

	std::string getMusic();

	static int sRetryCount;
private:
	sf::Sprite mBackground;
	Button mReturnToMain;
	Button mRetryLevel;
	std::string mMusic;
	sf::Text mRetryText;
	
	
};



#endif