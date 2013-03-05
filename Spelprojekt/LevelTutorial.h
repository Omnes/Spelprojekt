#ifndef LEVELTUTORIAL
#define LEVELTUTORIAL
#include "States.h"
#include "Taktikmeny.h"
#include <SFML\System\Clock.hpp>

class LevelTutorial : public States{

public:
	LevelTutorial();
	~LevelTutorial(); 
	virtual void update();
	virtual void render();
	virtual std::string getMusic();
	void setArrowPositions();
	void readAnimals(); 

private:

	std::string mMusic;
	TaktikMeny* mTaktik;
	sf::Clock mTimer1;
	sf::Clock mTimer2;
	bool mStartedTimer;
	sf::Sprite mArrow;
	std::vector<sf::Sprite> mArrows;

};



#endif