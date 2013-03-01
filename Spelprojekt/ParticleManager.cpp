#include "ParticleManager.h"
#include "ParticleSystem.h"
#include "ParticlePrototype.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Texture.hpp>
#include "tinyxml2.h"
#include "iostream"


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

	//ser till att vi nite laddar in en partikel som redan finns igen;
	PrototypeMap::iterator i;
	i = mPrototypeMap.find(name);
	if(i != mPrototypeMap.end()){
		std::cout<< std::endl << name << " is already loaded!";
		return;
	}

	//textur
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Texture");
	sf::Texture* texture = new sf::Texture; //resourceManager här istället;
	texture->loadFromFile(elm->GetText());
	int yframes = doc.FirstChildElement("Particle")->FirstChildElement("Texture")->IntAttribute("yframes");
	prototype->setTexture(texture,yframes);

	//life
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Life");
	int lifeMin = elm->IntAttribute("min");
	int lifeMax = elm->IntAttribute("max");
	prototype->setLife(lifeMin,lifeMax);

	//direction
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Direction");
	float directionMin = elm->FloatAttribute("min");
	float directionMax = elm->FloatAttribute("max");
	prototype->setDirection(directionMin, directionMax);

	//speed
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Speed");
	float speedMin = elm->FloatAttribute("min");
	float speedMax = elm->FloatAttribute("max");
	float speedIncrease = elm->FloatAttribute("increase");
	prototype->setSpeed(speedMin,speedMax,speedIncrease);

	//rotation
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Rotation");
	float rotationMin = elm->FloatAttribute("min");
	float rotationMax = elm->FloatAttribute("max");
	float rotationIncreaseMin = elm->FloatAttribute("increaseMin");
	float rotationIncreaseMax = elm->FloatAttribute("increaseMax");
	prototype->setRotation(rotationMin,rotationMax,rotationIncreaseMin,rotationIncreaseMax);

	//scale
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Scale");
	float scaleMin = elm->FloatAttribute("min");
	float scaleMax = elm->FloatAttribute("max");
	float scaleIncrease = elm->FloatAttribute("increase");
	prototype->setScale(scaleMin,scaleMax,scaleIncrease);

	//color
	const tinyxml2::XMLElement* col;
	elm = doc.FirstChildElement("Particle")->FirstChildElement("Color");

	col = elm->FirstChildElement("Start");
	sf::Color start = sf::Color(col->FloatAttribute("r"),col->FloatAttribute("g"),col->FloatAttribute("b"),col->FloatAttribute("a"));
	col = elm->FirstChildElement("End");
	sf::Color end = sf::Color(col->FloatAttribute("r"),col->FloatAttribute("g"),col->FloatAttribute("b"),col->FloatAttribute("a"));
	prototype->setColor(start,end);

	mPrototypeMap[name] = ParticlePrototype(*prototype);

	delete prototype;

}

void ParticleManager::loadAllParticlesFromFile(std::string filePath){
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath.c_str());

	tinyxml2::XMLElement* elm = doc.FirstChildElement();

	while(elm != 0){
		loadPrototype(elm->GetText());
		elm = elm->NextSiblingElement();
	}

}
