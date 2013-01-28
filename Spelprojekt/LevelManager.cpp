#include "LevelManager.h"
#include "tinyxml2.h"
#include <SFML\Graphics\Sprite.hpp>
#include "ResourceManager.h"
#include "StaticLayer.h"
#include "ActiveLayer.h"
#include <iostream>
#include "AnimalPrototype.h"



LevelManager::LevelManager(){
	mFilePath = "Level1.xml";
}



LevelManager::~LevelManager(){

}

LevelManager& LevelManager::getInst(){
	static LevelManager instance;
	return instance;
}

void LevelManager::setFilePath(std::string filePath){
	mFilePath = filePath;
}

std::vector<std::string> LevelManager::getAnimalsOnLevel(){
	std::vector<std::string> animalsOnLevel;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(mFilePath.c_str());

	tinyxml2::XMLElement *elm = doc.FirstChildElement("AnimalsOnLevel")->FirstChildElement();

	while (elm !=0){
		animalsOnLevel.push_back(elm->GetText());
		elm->NextSiblingElement();

	}

	return animalsOnLevel;
}

void LevelManager::setAnimalPosition(std::vector<Entity*> entityVector){
	placedAnimals = entityVector;

}

std::vector<Layer*> LevelManager::loadLayers(){
	std::vector<Layer*> layers;
	
	tinyxml2::XMLDocument doc;
	doc.LoadFile(mFilePath.c_str()); // den vill ha en const char *, lös skiten.  skiten är nu löst.

	tinyxml2::XMLElement *elm = doc.FirstChildElement("Layers")->FirstChildElement();
	while (elm != 0){
		std::cout << elm->Name() << std::endl;
		Layer *layer;

		ResourceManager* resourceManager = &ResourceManager::getInst();
		
		std::string layerType = elm->FirstChildElement("Layer")->GetText();
		std::cout << layerType << std::endl;
		if(layerType == "static"){
			const tinyxml2::XMLElement *img = elm->FirstChildElement("Images")->FirstChildElement();
			std::vector<sf::Sprite*> spriteVector;
			
			while(img != 0){

				sf::Texture* tex = resourceManager->getTexture(img->GetText());
				std::cout << img->GetText()<< std::endl;
				sf::Sprite *sprite = new sf::Sprite();
				sprite->setTexture(*tex);
				spriteVector.push_back(sprite);

				img = img->NextSiblingElement();
			}

			float speed = elm->FirstChildElement("Stats")->FirstAttribute()->FloatValue();
			std::cout << speed << std::endl;
			layer = new StaticLayer(spriteVector, speed);
		}
		if(layerType == "active"){

			std::vector<Entity*> entityVector(placedAnimals);


			//lägg in hinder
			//och eld


			layer = new ActiveLayer(entityVector);
		}

		layers.push_back(layer);

		elm = elm->NextSiblingElement();
	 	

	}

	return layers;
	
}




/*
ladda till taktikmenyn


längd på bana
inga hinder på varandra
min distans
min och max antal för varje hinder
eldens fart

*/