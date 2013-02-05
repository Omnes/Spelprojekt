#include "ActiveLayer.h"
#include "Entity.h"
#include "WindowManager.h"
#include "LevelManager.h"
#include "Camera.h"
#include "StateManager.h"

#include <iostream>

ActiveLayer::ActiveLayer(std::vector <Entity*> entityVector, int levellength):
	mEntityVector(entityVector),
	mLevellength(levellength),
	mAllAnimalsPassed(false)
{
	if(mEntityVector.empty()){
		std::cout<<"EntityVector is empty";
	}
	mThisCamera = 0;
}

ActiveLayer::~ActiveLayer(){}

void ActiveLayer::move(float cameraVelocity){

	//ska denna användas ?? <----------------------------------------------------'******
	//inte för tillfället men det skadar inte att den finns ett tag

}

void ActiveLayer::update(){

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		(*i)->update();
	}
	
	collision();
	killDead();
}

void ActiveLayer::render(){
	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}
}

void ActiveLayer::collision(){

	float AnimalMax = 0;

	if(LevelManager::getInst().getCamera() != nullptr && mThisCamera == 0){
		mThisCamera = LevelManager::getInst().getCamera();
	}else if(mThisCamera != 0){
		AnimalMax = mThisCamera->getMax();
	}

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		
		for(EntityVector::iterator j = mEntityVector.begin(); j != mEntityVector.end(); j++){
			//animalmax kan vara noll i början. kolla detta.
			if((AnimalMax + 70) > (*i)->getPos().x && (AnimalMax + 70) > (*j)->getPos().x){
				if((*i)->getSprite()->getGlobalBounds().intersects((*j)->getSprite()->getGlobalBounds()) && (*i)->getID() != (*j)->getID()){

					(*i)->collide((*j));
					(*j)->collide((*i));
				}	
			}
		}
	}
}

void ActiveLayer::killDead(){

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end();){

		if((*i)->getAlive() == false){
			delete (*i);
			i = mEntityVector.erase(i);
		}else{
			i++;
		}

	}

}

std::vector<Entity*>* ActiveLayer::getEntityVector(){
	return &mEntityVector;
}

void ActiveLayer::finishLine(){

	mAllAnimalsPassed = true;

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end();){

		if((*i)->getID() == "Animal"){
			if((*i)->getPos().x<mLevellength){
				mAllAnimalsPassed = false;
			}
		}
	}

	if(mAllAnimalsPassed == true){

		for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end();){
			if((*i)->getID() == "Animal"){
				if((*i)->getPos().x>mLevellength){
					mAliveEntityVector.push_back(*i);
				}
			}
		}
		StateManager::getInst().addState("levelfinished");
	}
}

std::vector<Entity*>* ActiveLayer::getAliveAnimals(){

	return &mAliveEntityVector;
}