#include "WorldMap.h"
#include <SFML\Graphics\CircleShape.hpp>
#include "WindowManager.h"

WorldMap::WorldMap(){}

WorldMap::~WorldMap(){}

void WorldMap::update(){}

void WorldMap::render(){

	sf::CircleShape circle(10.0);
	WindowManager::getInst().getWindow()->draw(circle);
}
