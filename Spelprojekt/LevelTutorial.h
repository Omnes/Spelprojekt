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
	void readAnimals(); 

private:

	float mIntroLength, mStep1, mStep2, mStep3;
	std::string mMusic;
	TaktikMeny* mTaktik;
	sf::Clock mTimer1;
	sf::Clock mTimer2;
	bool mStartedTimer, mS1Played;
	sf::Sprite mArrow, mSpot, mObst1, mObst2, mSteer, mScroll;


};



#endif