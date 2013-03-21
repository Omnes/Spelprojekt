#ifndef LEVELTUTORIAL
#define LEVELTUTORIAL
#include "States.h"
#include "Taktikmeny.h"
#include "FakeAbilityButton.h"
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

	float mIntroLength, mStep1, mStep2;
	std::string mMusic;
	TaktikMeny* mTaktik;
	sf::Clock mTimer1;
	sf::Clock mTimer2;
	bool mStartedTimer;
	sf::Sprite mArrow, mSpot, mSteer, mScroll;
	typedef std::vector <FakeAbilityButton*> AbilityButton;
	AbilityButton mAbilityButtons;


};



#endif