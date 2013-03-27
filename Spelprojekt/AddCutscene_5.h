#ifndef ADDCUTSCENE_5
#define ADDCUTSCENE_5

#include "Event.h"
#include "StateManager.h"
#include "Cutscene.h"
#include "WindowManager.h"
#include <SFML\Graphics\Sprite.hpp>

class AddCutscene_5 : public Event{

public:
	AddCutscene_5(){}
	~AddCutscene_5(){}
	virtual void update(){
		sf::Sprite loadingscreen(*ResourceManager::getInst().getTexture("resources/Menu/LevelFinished.png"));
		WindowManager::getInst().getWindow()->draw(loadingscreen);
		WindowManager::getInst().getWindow()->display();
		StateManager::getInst().addState(new Cutscene("Resources/Data/Cutscenes/Cutscene_Credits.xml"));
	}

};

#endif