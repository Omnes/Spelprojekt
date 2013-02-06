#include "WorldMap.h"
#include "WindowManager.h"
WorldMap::WorldMap(){
	mButtons.push_back(new LevelButton(sf::Vector2f(200,100), "addTaktik","knapp1.jpg", "Level1.xml"));

	mButtons.push_back(new LevelButton(sf::Vector2f(200,300), "addGameplay","knapp3.jpg","Level1.xml"));
}

WorldMap::~WorldMap(){}

void WorldMap::update(){
	for (std::vector<LevelButton*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		(*i)->update();
	}
}

void WorldMap::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	for (std::vector<LevelButton*>::iterator i = mButtons.begin(); i != mButtons.end(); i++){
		window->draw((*i)->getSprite());
	}
}
