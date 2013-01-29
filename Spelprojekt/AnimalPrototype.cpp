#include "AnimalPrototype.h"
#include "Animal.h"
#include "ResourceManager.h"
#include "Animation.h"


AnimalPrototype::AnimalPrototype(std::string filePath){
	loadAnimal(filePath);
	mSprite.setTexture(*mTex);
	mSprite.setTextureRect(sf::IntRect(0,0,mTex->getSize().x,mTex->getSize().y));
}

AnimalPrototype::~AnimalPrototype(){}

void AnimalPrototype::loadAnimal(std::string filePath){

	tinyxml2::XMLDocument doc;

	doc.LoadFile(filePath.c_str()); //variabel h�r

	//skapar dokument
	tinyxml2::XMLElement *elm = doc.FirstChildElement("Animal");

	ResourceManager* resourceManager = &ResourceManager::getInst();

	//kollar f�rsta elementet i xml-filen
	const tinyxml2::XMLElement *img = elm->FirstChildElement("Images")->FirstChildElement();

	//s�tter textur
	mTex = resourceManager->getTexture(img->GetText()); // kan nog inte vara lokal

	//kollar andra elemntet som har flera attribut
	const tinyxml2::XMLAttribute *speed = elm->FirstChildElement("Speed")->FirstChildElement()->FirstAttribute();

	//s�tter attribut
	mGroundSpeed = speed->FloatValue();
	speed->Next();
	mMiddleSpeed = speed->FloatValue();
	speed->Next();
	mTreeSpeed = speed->FloatValue();

	//kollar tredje elemntet
	const tinyxml2::XMLElement *animalType = elm->FirstChildElement("AnimalType")->FirstChildElement();

	//s�tter animaltype till vilken typ av djur det �r rovdjur/v�xt�tare
	mAnimalType = animalType->GetText();

	const tinyxml2::XMLAttribute *imageAttr = elm->FirstChildElement("ImageAttr")->FirstChildElement()->FirstAttribute();

	//s�tter attribut
	mFrameTick = imageAttr->FloatValue();
	imageAttr->Next();
	mFrames = imageAttr->FloatValue();
	
}

Animal* AnimalPrototype::createAnimal(){

	mAnimation =  new Animation(mTex, mFrameTick, mFrames);

	return new Animal(mAnimation, sf::Vector2f(2,2), 0);
	//return new Animal(mAnimation, vilken position nn  , r�kna ut speed h�r);
};

sf::Vector2f AnimalPrototype::getPos(){
	return mPosition;
}

void AnimalPrototype::setPos(sf::Vector2f position){

	mPosition = position;
}

sf::FloatRect& AnimalPrototype::getGlobalBounds(){
	return mSprite.getGlobalBounds();
}