#ifndef WORLDMAPTUTORIAL
#define WORLDMAPTUTORIAL
#include "States.h"
#include "WorldMap.h"
#include <SFML\System\Clock.hpp>

class WorldMapTutorial : public States{

public:
	WorldMapTutorial();
	~WorldMapTutorial(); 
	virtual void update();
	virtual void render();
	virtual std::string getMusic();
	void setArrowPositions();

private:

	std::string mMusic;
	WorldMap* mWorldMap;
	sf::Clock mTimer;
	sf::Sprite mArrow;
	std::vector<sf::Sprite> mArrows;

};



#endif