#ifndef GAMEOVER
#define GAMEOVER

#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Button.h"


class GameOver: public States{
public:
	GameOver();
	~GameOver();
	virtual void update();
	virtual void render();

	std::string getMusic();


private:
	sf::Sprite mBackground;
	Button mReturnToMain;
	Button mLoadLast;
	std::string mMusic;
	
};



#endif