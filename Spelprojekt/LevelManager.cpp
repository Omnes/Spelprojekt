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
#include "Fire.h"



LevelManager::LevelManager() : 
	mLevellength(0){
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

std::vector<AnimalPrototype*> LevelManager::getAnimalsOnLevel(){
	std::vector<AnimalPrototype*> animalsOnLevel;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(mFilePath.c_str());

	tinyxml2::XMLElement *elm = doc.FirstChildElement("AnimalsOnLevel")->FirstChildElement();

	while (elm !=0){
		animalsOnLevel.push_back(new AnimalPrototype(elm->GetText()));
		elm = elm->NextSiblingElement();

	}

	for (std::vector<std::string>::iterator i = mAliveAnimals.begin();i != mAliveAnimals.end();i++){
		animalsOnLevel.push_back(new AnimalPrototype(*i));
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

			mLevellength = doc.FirstChildElement("Level")->FirstAttribute()->IntValue();

			float x = 500 + rand()%200;


			while(x < mLevellength){
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
				atr = atr->Next();
				float y = atr->FloatValue();
			
			
				std::string id = obst->Name();
				sf::Vector2f pos = sf::Vector2f(x,y);
				sf::Texture* tex = ResourceManager::getInst().getTexture(obst->GetText());
				Obstacle* obstacle = new Obstacle(tex, pos, speedMod, id);
				entityVector.push_back(obstacle);

				x += minDistance + rand() % (maxDistance - minDistance);
			
			}

			float fireSpeed = doc.FirstChildElement("Fire")->FirstAttribute()->FloatValue();
			entityVector.push_back(new Fire(sf::Vector2f(0,0),fireSpeed));

			entityVector.push_back(new Animal(new Animation(resourceManager->getTexture("groda.png"),100,10),sf::Vector2f(100,400),2));
			

			ActiveLayer* activeLayer = new ActiveLayer(entityVector, mLevellength);
			layer = activeLayer;
			mActiveLayer = activeLayer;
		}  

		layers.push_back(layer);
		
		elm = elm->NextSiblingElement();
	 	

	}

	return layers;
	
}

ActiveLayer* LevelManager::getActiveLayer(){
	return mActiveLayer;
}

void LevelManager::setCamera(Camera* levelCamera){
	mThisCamera = levelCamera;
}

Camera* LevelManager::getCamera(){
	return mThisCamera;
}

int LevelManager::getLevelLength(){

	return mLevellength;
}

void LevelManager::setAliveAnimals(std::vector<std::string>& aliveVector){
	mAliveAnimals = aliveVector;
}