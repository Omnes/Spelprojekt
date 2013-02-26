#ifndef ANIMALIPEDIA
#define ANIMALIPEDIA

#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Button.h"
#include "AnimalipediaButton.h"
#include <vector>
#include <string>
#include "Info.h"
#include "PageButton.h"


class Animalipedia: public States{
public:
	Animalipedia();
	~Animalipedia();
	virtual void update();
	virtual void render();
	void loadUnlocked();
	void setInfo(std::string name);
	std::string getInfo();
	void setPage(int number);
	int getPage();

	std::string getMusic();


private:
	int mCurrentButtonPage;
	int mButtonsPerPage;
	Info* mInfo;
	sf::Sprite mBackground;
	std::string mMusic;
	std::vector<AnimalipediaButton*> mButtonVector;
	std::vector<AnimalipediaButton*> mActiveButtons;

	std::string mInfoName;

	PageButton mUpButton;
	PageButton mDownButton;

	
};



#endif