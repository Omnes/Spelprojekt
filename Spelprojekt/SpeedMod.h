#ifndef SPEEDMOD
#define SPEEDMOD

#include <SFML\System\Clock.hpp>

class SpeedMod{
public:
	SpeedMod(float time, float mod);
	~SpeedMod();

	float getMod();
	bool getAlive();

private:
	float mAliveTime;
	float mMod;
	sf::Clock clock;



};



#endif
