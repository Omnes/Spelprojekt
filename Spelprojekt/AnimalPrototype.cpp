#include "AnimalPrototype.h"
#include "Animal.h"
#include "ResourceManager.h"
#include "Animation.h"


AnimalPrototype::AnimalPrototype(std::string filePath){
	loadAnimal(filePath);
	mSprite.setTexture(*mTex);
	mSprite.setTextureRect(sf::IntRect(0,0,mTex->getSize().x/3,mTex->getSize().y));
	mSprite.setOrigin(64,64); // kom ihåg att fixa orgin när vi fått grafik
	mFilePath = filePath;
}

AnimalPrototype::~AnimalPrototype(){}

void AnimalPrototype::loadAnimal(std::string filePath){

	tinyxml2::XMLDocument doc;

	doc.LoadFile(filePath.c_str()); //variabel här

	//skapar dokument
	tinyxml2::XMLElement *elm = doc.FirstChildElement("Animal");

	ResourceManager* resourceManager = &ResourceManager::getInst();

	//kollar första elementet i xml-filen
	const tinyxml2::XMLElement *img = elm->FirstChildElement("Images");

	//sätter textur
	mTex = resourceManager->getTexture(img->GetText()); // kan nog inte vara lokal

	//kollar andra elemntet som har flera attribut
	const tinyxml2::XMLAttribute *speed = elm->FirstChildElement("Speed")->FirstAttribute();

	//sätter attribut
	//ground
	mSpeedVector.push_back(speed->FloatValue());
	speed = speed->Next();
	//middle
	mSpeedVector.push_back(speed->FloatValue());
	speed = speed->Next();
	//air
	mSpeedVector.push_back(speed->FloatValue());
	

	//kollar tredje elemntet
	const tinyxml2::XMLElement *animalType = elm->FirstChildElement("AnimalType");

	//sätter animaltype till vilken typ av djur det är rovdjur/växtätare
	mAnimalType = animalType->GetText();

	const tinyxml2::XMLAttribute *imageAttr = elm->FirstChildElement("ImageAttr")->FirstAttribute();

	//sätter attribut
	mFrameTick = imageAttr->FloatValue();
	imageAttr = imageAttr->Next();
	mFrames = imageAttr->FloatValue();
	
}

Animal* AnimalPrototype::createAnimal(float standardSpeed){

	mAnimation =  new Animation(mTex, mFrameTick, mFrames);
	//mStandardSpeed = 0; //denna ska vara med. inte noll
	return new Animal(mAnimation, mPosition, standardSpeed); // animal tar en sträng också

};

sf::Vector2f AnimalPrototype::getPos(){
	return mPosition;
}

void AnimalPrototype::setPos(sf::Vector2f position){
	mSprite.setPosition(position);
	mPosition = position;
}

void AnimalPrototype::setStartPos(sf::Vector2f	startPos){
	mStartPos = startPos;
}

sf::Vector2f AnimalPrototype::getStartPos(){
	return mStartPos;
}

sf::FloatRect& AnimalPrototype::getGlobalBounds(){
	return mSprite.getGlobalBounds();
}

sf::Sprite* AnimalPrototype::getSprite(){
	return &mSprite;
}

int AnimalPrototype::getLevel(){
	float temp = 0;
	for(SpeedVector::size_type i = 0 ; i < mSpeedVector.size(); i++){
		if(mSpeedVector[i] > temp){
			temp = mSpeedVector[i];
			mHighSpeed = i;
		}
	}
	return mHighSpeed;
}

std::vector <float> AnimalPrototype::getSpeedVector(){
	return mSpeedVector;
}

