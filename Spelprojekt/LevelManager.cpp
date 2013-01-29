#include "LevelManager.h"
#include "tinyxml2.h"
#include <SFML\Graphics\Sprite.hpp>
#include "ResourceManager.h"
#include "StaticLayer.h"
#include "ActiveLayer.h"
#include <iostream>
#include "AnimalPrototype.h"
#include "Obstacle.h"
#include "Animal.h"
#include "Animation.h"



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
		elm = elm->NextSiblingElement();

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

			int minDistance = doc.FirstChildElement("Obstacles")->FirstAttribute()->IntValue();
			int maxDistance = doc.FirstChildElement("Obstacles")->FirstAttribute()->Next()->IntValue();

			std::map<int,std::string> mChanceMap;

			tinyxml2::XMLElement *obst = doc.FirstChildElement("Obstacles")->FirstChildElement();

			while(obst != 0){
				const tinyxml2::XMLAttribute *atr = obst->FirstAttribute();

				mChanceMap[atr->IntValue()] = obst->Name();
				obst = obst->NextSiblingElement();
			}

			int levelLength = doc.FirstChildElement("Level")->FirstAttribute()->IntValue();

			float x = 500 + rand()%200;


			while(x < levelLength){
				std::string name = "Stone";

				int randNumber = rand()%100;
				int currentNumber = 0;

				for(std::map<int,std::string>::iterator i = mChanceMap.begin(); i != mChanceMap.end(); i++){
					currentNumber += i->first;

					if (currentNumber > randNumber){
						name = i->second;
						break;
					}
				
				}

				obst = doc.FirstChildElement("Obstacles")->FirstChildElement(name.c_str());
				const tinyxml2::XMLAttribute *atr = obst->FirstAttribute()->Next();

				float speedMod = atr->FloatValue();
				atr->Next();
				float y = atr->FloatValue();
			
			
				std::string id = obst->GetText();
				sf::Vector2f pos = sf::Vector2f(x,y);
				sf::Texture* tex = ResourceManager::getInst().getTexture(obst->GetText());
				Obstacle* obstacle = new Obstacle(tex, pos, speedMod, id);
				entityVector.push_back(obstacle);

				x += minDistance + rand()%(maxDistance - minDistance);
			
			}

			entityVector.push_back(new Animal(new Animation(resourceManager->getTexture("katt.jpg"),300,3),sf::Vector2f(0,400),1));

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