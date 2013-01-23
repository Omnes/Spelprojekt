#include "LevelManager.h"
#include "tinyxml2.h"
#include <SFML\Graphics\Sprite.hpp>
#include "ResourceManager.h"
#include "StaticLayer.h"
#include "ActiveLayer.h"



LevelManager::LevelManager(){

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

//std::vector<Place_Animal*> LevelManager::getAnimalsOnLevel(){
//	return std::vector<Place_Animal*>;
//}

void LevelManager::setAnimalPosition(std::vector<Entity*> entityVector){
	placedAnimals = entityVector;

}

std::vector<Layer*> LevelManager::loadLayers(){
	std::vector<Layer*> layers;
	
	tinyxml2::XMLDocument doc;
	doc.LoadFile(/*mFilePath*/ "Fisk.xml"); // den vill ha en const char *, lös skiten.

	tinyxml2::XMLElement *elm = doc.FirstChildElement();
	while (elm != 0){
		Layer *layer;

		ResourceManager* resourceManager = &ResourceManager::getInst();

		if(elm->FirstChildElement("Layer")->GetText() == "static"){
			const tinyxml2::XMLElement *img = elm->FirstChildElement("Images")->FirstChildElement();
			std::vector<sf::Sprite*> spriteVector;
			
			while(img != 0){

				sf::Texture* tex = resourceManager->getTexture(img->GetText());
				sf::Sprite *sprite = new sf::Sprite();
				sprite->setTexture(*tex);
				spriteVector.push_back(sprite);

				img = img->NextSiblingElement();
			}

			float speed = elm->FirstChildElement("Stats")->FirstAttribute()->FloatValue();
			layer = new StaticLayer(spriteVector, speed);
		}
		if(elm->FirstChildElement("Layer")->GetText() == "active"){

			std::vector<Entity*> entityVector(placedAnimals);


			//lägg in hinder
			//och eld


			layer = new ActiveLayer(entityVector);
		}

		layers.push_back(layer);
		elm->NextSiblingElement();

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