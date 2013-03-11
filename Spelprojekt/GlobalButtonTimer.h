#ifndef GLOBALBUTTONTIMER
#define GLOBALBUTTONTIMER

#include <SFML\System\Clock.hpp>

class GlobalButtonTimer{
public:
	static sf::Clock sGlobalTimer;
	static float sCooldown;

	GlobalButtonTimer(){
		sCooldown = 0.3f;
	}

	static bool onCoolDown(){
		return sGlobalTimer.getElapsedTime().asSeconds() > sCooldown;
	}

	static void globalRestart(){
		sGlobalTimer.restart();
	}

	
};


#endif