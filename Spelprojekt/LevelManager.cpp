#include "LevelManager.h"
#include "tinyxml2.h"
#include <SFML\Graphics\Sprite.hpp>
#include "ResourceManager.h"
#include "ParticleManager.h"
#include "StaticLayer.h"
#include "ActiveLayer.h"
#include <iostream>
#include "AnimalPrototype.h"
#include "Obstacle.h"
#include "Animal.h"
#include "Animation.h"
#include "Fire.h"
/*
**********************************************************************
								Notes
	spara TinyEXML::doc istället för en sträng (mFilePath)

**********************************************************************
*/


LevelManager::LevelManager() : 
	mLevellength(0){
	mFilePath = "Resources/Data/Level/Jungle_Level1.xml";
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
std::string LevelManager::getFilePath(){

	return mFilePath;
}

std::vector <AnimalPrototype*> LevelManager::getAnimalsOnLevel(){
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

void LevelManager::setAnimalPosition(std::vector <Entity*> entityVector){
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

<<<<<<< HEAD
			std::map<std::string, int> mChanceMap;
=======
			std::map<std::string,int> mChanceMap;
>>>>>>> master

			tinyxml2::XMLElement *obst = doc.FirstChildElement("Obstacles")->FirstChildElement();


			int totalChanceValue = 0;

			while(obst != 0){
				const tinyxml2::XMLAttribute *atr = obst->FirstAttribute();
				totalChanceValue += atr->IntValue();
				mChanceMap[obst->Name()] = atr->IntValue();
				obst = obst->NextSiblingElement();
			}

			mLevellength = doc.FirstChildElement("Level")->FirstAttribute()->IntValue();

			float x = 1280 + rand()%100;

			int minDistanceFromGoal = 250;


			while(x < mLevellength - minDistanceFromGoal){
				std::string name;

				int randNumber = rand()%totalChanceValue;
				int currentNumber = 0;

				for(std::map<std::string,int>::iterator i = mChanceMap.begin(); i != mChanceMap.end(); i++){
					currentNumber += i->second;

					if (currentNumber > randNumber){
						name = i->first;
						break;
					}
				
				}

				obst = doc.FirstChildElement("Obstacles")->FirstChildElement(name.c_str());
				const tinyxml2::XMLAttribute *atr = obst->FirstAttribute()->Next();

				float speedMod = atr->FloatValue();
				atr = atr->Next();
				float y = atr->FloatValue();
				atr = atr->Next();
				int xframes = atr->IntValue();
				atr = atr->Next();
				float frameTime = atr->IntValue();
			
			
				std::string id = obst->Name();
				sf::Vector2f pos = sf::Vector2f(x,y);
				sf::Texture* tex = ResourceManager::getInst().getTexture(obst->GetText());

				Animation* animation = new Animation(tex,200,xframes,1);
				Obstacle* obstacle = new Obstacle(animation, pos, speedMod, id);
				entityVector.push_back(obstacle);

				x += minDistance + rand() % (maxDistance - minDistance);
			
			}

			//skapar elden
			float fireSpeed = doc.FirstChildElement("Fire")->FirstAttribute()->FloatValue();
			float acceleration = doc.FirstChildElement("Fire")->FirstAttribute()->Next()->FloatValue();
			entityVector.push_back(new Fire(sf::Vector2f(-150,0),fireSpeed,acceleration));

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

void LevelManager::setDeadAnimals(std::vector<std::string>& deadVector){

	for(int i = 0; i < deadVector.size();i++){
		mDeadAnimalCollection.push_back(deadVector[i]);
	}

	mDeadAnimals = deadVector;
}

std::vector<std::string> LevelManager::getAliveAnimals(){

	return mAliveAnimals;
}

std::vector<std::string> LevelManager::getDeadAnimals(){

	return mDeadAnimals;
}

std::vector<std::string>* LevelManager::getDeadAnimalCollection(){
	return &mDeadAnimalCollection;
}

std::vector<float> LevelManager::getLevelsOnLevel(){
	tinyxml2::XMLDocument doc;
	doc.LoadFile(mFilePath.c_str());

	const tinyxml2::XMLAttribute* attr = doc.FirstChildElement("LevelsYValue")->FirstAttribute();
	
	std::vector<float>LevelYVector;

	while(attr != 0){
		LevelYVector.push_back(attr->FloatValue());
		attr = attr->Next();
	}

	return LevelYVector;
}


std::string LevelManager::getMusicOnLevel(){
	tinyxml2::XMLDocument doc;
	doc.LoadFile(mFilePath.c_str());

	return doc.FirstChildElement("Music")->GetText();
	

}

std::vector<std::string> LevelManager::getAbilitiesOnLevel(){
	std::vector<std::string> vector;

	tinyxml2::XMLDocument doc;
	doc.LoadFile(mFilePath.c_str());

	tinyxml2::XMLElement *elem = doc.FirstChildElement("Abilities")->FirstChildElement();

	while(elem != 0){
		vector.push_back(elem->GetText());
		elem = elem->NextSiblingElement();
	}

	return vector;

}

std::string LevelManager::getGuiTextureFilepath(){
	tinyxml2::XMLDocument doc;
	doc.LoadFile(mFilePath.c_str());
	return doc.FirstChildElement("Gui")->GetText();
}