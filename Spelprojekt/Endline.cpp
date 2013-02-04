#include "Endline.h"


Endline::Endline(sf::Vector2f position) : mPosition(position){
}

Endline::~Endline(){
}

void Endline::update(){
}


sf::FloatRect* Endline::getRect(){

	sf::FloatRect derp;

	return &derp;
}

sf::Sprite* Endline::getSprite(){
	sf::Sprite herp;

	return &herp;
}

bool Endline::getAlive(){
	return true;
}

void Endline::setAlive(bool alive){

}
	
void Endline::collide(Entity* entity){

}

void Endline::setMod(SpeedMod* speedMod){

}

std::string Endline::getID(){

	std::string mhm;
	return mhm;
}

sf::Vector2f Endline::getPos(){

	sf::Vector2f mmhm;
	return mmhm;
}