#ifndef TUTORIAL
#define TUTORIAL
#include "States.h"
#include "Taktikmeny.h"
#include <SFML\System\Clock.hpp>

class Tutorial : public States{

public:
	Tutorial();
	~Tutorial(); 
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