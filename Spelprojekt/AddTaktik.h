#ifndef ADDTAKTIK
#define ADDTAKTIK
#include "Event.h"
#include "StateManager.h"
#include "Taktikmeny.h"
#include <SFML\Graphics\Sprite.hpp>
#include "WindowManager.h"
#include "ResourceManager.h"

class AddTaktik : public Event{

public:

	AddTaktik(){}
	~AddTaktik(){}
	virtual void update(){
		sf::Sprite loadingscreen(*ResourceManager::getInst().getTexture("resources/Menu/LevelFinished.png"));
		WindowManager::getInst().getWindow()->draw(loadingscreen);
		WindowManager::getInst().getWindow()->display();
		StateManager::getInst().addState(new TaktikMeny);
	}

};

#endif 