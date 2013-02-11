#include "ParticleManager.h"
#include "ParticleSystem.h"
#include "ParticlePrototype.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Texture.hpp>
#include "tinyxml2.h"


ParticleManager::ParticleManager(){
	ParticlePrototype::init();
}

ParticleManager& ParticleManager::getInst(){
	static ParticleManager instance;
	return instance;
}


ParticleManager::~ParticleManager(){
}

void ParticleManager::addSystem(ParticleSystem* ps){

	mSystems.push_back(ps);
}

int ParticleManager::getActiveParticleCount(){

	int count = 0;
	for(Systems::iterator i = mSystems.begin(); i != mSystems.end(); i++){
		count += (*i)->getActiveParticles();
	}
	return count;
}

void ParticleManager::removeSystem(ParticleSystem* ps){

	for(Systems::iterator i = mSystems.begin(); i != mSystems.end(); i++){

		if (*i == ps){
			i = mSystems.erase(i);
			return;
		}
	}
}

void ParticleManager::update(){
	
	for(Systems::iterator i = mSystems.begin(); i != mSystems.end(); i++){
		(*i)->update();
	}
}

void ParticleManager::render(sf::RenderWindow& window){
	
	for(Systems::iterator i = mSystems.begin(); i != mSystems.end(); i++){
		(*i)->render(window);
	}
}

ParticlePrototype& ParticleManager::getPrototype(std::string name){

	return mPrototypeMap.find(name)->second;
}

void ParticleManager::savePrototype(ParticlePrototype &prototype,std::string name){

	mPrototypeMap[name] = ParticlePrototype(prototype);
}

void ParticleManager::loadPrototype(std::string filePath){

	ParticlePrototype* prototype = new ParticlePrototype;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());

	//namn
	tinyxml2::XMLElement* elm = doc.FirstChildElement("Particle")->FirstChildElement("Name");
	std::string name = elm->GetText();

	//textur
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Texture");
	sf::Texture* texture = new sf::Texture; //resourceManager här istället;
	texture->loadFromFile(elm->GetText());
	int yframes = doc.FirstChildElement("Particle")->FirstChildElement("Texture")->FirstAttribute()->IntValue();
	prototype->setTexture(texture,yframes);

	//life
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Life");
	int lifeMin = elm->FirstAttribute()->IntValue();
	int lifeMax = elm->FirstAttribute()->Next()->IntValue();
	prototype->setLife(lifeMin,lifeMax);

	//direction
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Direction");
	float directionMin = elm->FirstAttribute()->FloatValue();
	float directionMax = elm->FirstAttribute()->Next()->FloatValue();
	prototype->setDirection(directionMin, directionMax);

	//speed
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Speed");
	float speedMin = elm->FirstAttribute()->FloatValue();
	float speedMax = elm->FirstAttribute()->Next()->FloatValue();
	float speedIncrease = elm->FirstAttribute()->Next()->Next()->FloatValue();
	prototype->setSpeed(speedMin,speedMax,speedIncrease);

	//rotation
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Rotation");
	float rotationMin = elm->FirstAttribute()->FloatValue();
	float rotationMax = elm->FirstAttribute()->Next()->FloatValue();
	float rotationIncreaseMin = elm->FirstAttribute()->Next()->Next()->FloatValue();
	float rotationIncreaseMax = elm->FirstAttribute()->Next()->Next()->Next()->FloatValue();
	prototype->setRotation(rotationMin,rotationMax,rotationIncreaseMin,rotationIncreaseMax);

	//scale
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Scale");
	float scaleMin = elm->FirstAttribute()->FloatValue();
	float scaleMax = elm->FirstAttribute()->Next()->FloatValue();
	float scaleIncrease = elm->FirstAttribute()->Next()->Next()->FloatValue();
	prototype->setScale(scaleMin,scaleMax,scaleIncrease);

	//color
	const tinyxml2::XMLAttribute* col;
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Color");

	col = elm->FirstChildElement("Start")->FirstAttribute();
	sf::Color start = sf::Color(col->FloatValue(),col->Next()->FloatValue(),col->Next()->Next()->FloatValue(),col->Next()->Next()->Next()->FloatValue());
	col = elm->FirstChildElement("End")->FirstAttribute();
	sf::Color end = sf::Color(col->FloatValue(),col->Next()->FloatValue(),col->Next()->Next()->FloatValue(),col->Next()->Next()->Next()->FloatValue());
	prototype->setColor(start,end);

	mPrototypeMap[name] = ParticlePrototype(*prototype);

	delete prototype;

}
