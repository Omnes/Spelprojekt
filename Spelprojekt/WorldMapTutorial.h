#ifndef WORLDMAPTUTORIAL
#define WORLDMAPTUTORIAL
#include "States.h"
#include "WorldMap.h"
#include "StateManager.h"
#include <SFML\System\Clock.hpp>
#include "AchievementState.h"

class WorldMapTutorial : public States{

public:
	WorldMapTutorial();
	~WorldMapTutorial(); 
	virtual void update();
	virtual void render();
	virtual std::string getMusic();

private:

	std::string mMusic;
	WorldMap* mWorldMap;
	sf::Clock mTimer;
	sf::Sprite mArrow;
	sf::Sprite mArrow2;
	float mTutorialDuration;

};



#endif