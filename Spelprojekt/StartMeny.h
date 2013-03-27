#ifndef STARTMENY
#define STARTMENY
#include "Button.h"
#include "States.h"
#include "LoadButton.h"

class StartMeny: public States{
public:
	virtual void update();
	virtual void render();
	StartMeny();
	~StartMeny();

	std::string getMusic();

private:
	std::vector<Button*> mButtons;
	std::string mMusic;

	LoadButton *mLoadButton;

	sf::Sprite mBackground;
	
};


#endif