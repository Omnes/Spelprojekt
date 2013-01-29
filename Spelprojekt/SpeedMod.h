#ifndef SPEEDMOD
#define SPEEDMOD

#include <SFML\System\Clock.hpp>
#include <string>

class SpeedMod{
public:
	SpeedMod(float time, float mod, std::string ID);
	~SpeedMod();

	float getMod();
	bool getAlive();
	std::string getID();

private:
	float mAliveTime;
	float mMod;
	sf::Clock mclock;
	std::string mID;


};



#endif
