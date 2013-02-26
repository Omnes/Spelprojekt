#ifndef ANIMALIPEDIA
#define ANIMALIPEDIA

#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Button.h"
#include "AnimalipediaButton.h"
#include <vector>
#include <string>
#include "Info.h"


class Animalipedia: public States{
public:
	Animalipedia();
	~Animalipedia();
	virtual void update();
	virtual void render();
	void loadUnlocked();
	void setInfo(std::string name);
	std::string getInfo();

	std::string getMusic();


private:

	Info* mInfo;
	sf::Sprite mBackground;
	std::string mMusic;
	std::vector<AnimalipediaButton*> mButtonVector;

	std::string mInfoName;
	
};



#endif