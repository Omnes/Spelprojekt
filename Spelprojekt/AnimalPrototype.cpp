#include "AnimalPrototype.h"
#include "Animal.h"
#include "ResourceManager.h"
#include "Animation.h"
#include "SoundManager.h"


AnimalPrototype::AnimalPrototype(std::string filePath):
	mExtraSpeed(1)
{
	loadAnimal(filePath);
	mSprite.setTexture(*mTex);
	mSprite.setTextureRect(sf::IntRect(0,mTex->getSize().y/2,mTex->getSize().x/10,mTex->getSize().y/2));
	mSprite.setOrigin(64,64); // kom ih�g att fixa orgin n�r vi f�tt grafik
	mFilePath = filePath;
}

AnimalPrototype::~AnimalPrototype(){}

void AnimalPrototype::loadAnimal(std::string filePath){

	tinyxml2::XMLDocument doc;

	doc.LoadFile(filePath.c_str()); //variabel h�r

	//skapar dokument
	tinyxml2::XMLElement *elm = doc.FirstChildElement("Animal");

	ResourceManager* resourceManager = &ResourceManager::getInst();

	//kollar f�rsta elementet i xml-filen
	const tinyxml2::XMLElement *img = elm->FirstChildElement("Images");

	//s�tter textur
	mTex = resourceManager->getTexture(img->GetText()); // kan nog inte vara lokal

	//kollar andra elemntet som har flera attribut
	//const tinyxml2::XMLAttribute *speed = elm->FirstChildElement("Speed")->FloatAttribute("air");

	//s�tter attribut
	mSpeedVector.push_back(elm->FirstChildElement("Speed")->FloatAttribute("air"));
	mSpeedVector.push_back(elm->FirstChildElement("Speed")->FloatAttribute("middle"));
	mSpeedVector.push_back(elm->FirstChildElement("Speed")->FloatAttribute("ground"));
	

	//kollar tredje elemntet
	const tinyxml2::XMLElement *animalType = elm->FirstChildElement("AnimalType");

	//s�tter animaltype till vilken typ av djur det �r rovdjur/v�xt�tare
	mAnimalType = animalType->GetText();

	const tinyxml2::XMLAttribute *imageAttr = elm->FirstChildElement("ImageAttr")->FirstAttribute();

	//s�tter attribut
	mFrameTick = elm->FirstChildElement("ImageAttr")->FloatAttribute("fTick");
	mFrames = elm->FirstChildElement("ImageAttr")->FloatAttribute("frames");

	//sound
	const tinyxml2::XMLElement *xmlSound = elm->FirstChildElement("Sound");

	std::string animalSound = xmlSound->GetText();

	mSound.setBuffer(*resourceManager->getSoundBuffer(animalSound));
	
}

Animal* AnimalPrototype::createAnimal(/*float bonusSpeed*/){

	mAnimation =  new Animation(mTex, mFrameTick, mFrames,2);// funkar alla parametrar ? jad�!
	return new Animal(mAnimation, mPosition, mStandardSpeed*mExtraSpeed, mFilePath); 

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

void AnimalPrototype::setStandardSpeed(float stdSpeed){
	mStandardSpeed = stdSpeed;
}

sf::FloatRect AnimalPrototype::getGlobalBounds(){
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

void AnimalPrototype::playSound(){
	SoundManager::getInst().play(mSound);
};

void AnimalPrototype::setExtraSpeed(float extraSpeed){
		mExtraSpeed = extraSpeed; 
}

std::string AnimalPrototype::getAnimalType(){
	return mAnimalType;
}

