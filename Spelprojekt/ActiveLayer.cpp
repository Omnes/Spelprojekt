#include "ActiveLayer.h"
#include "Entity.h"
#include "WindowManager.h"
#include "LevelManager.h"
#include "StateManager.h"
#include "Camera.h"
#include "EventManager.h"

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

ActiveLayer::~ActiveLayer(){
	while(!mEntityVector.empty()){
		delete mEntityVector.back();
		mEntityVector.pop_back();
	}
}

void ActiveLayer::move(float cameraVelocity){

	//ska denna användas ?? <----------------------------------------------------'****** /sean xoxo <3
	//inte för tillfället men det skadar inte att den finns ett tag /robin

}

void ActiveLayer::update(){

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		(*i)->update();
	}
	for(std::vector<Animation*>::iterator i = mAnimationVector.begin(); i != mAnimationVector.end();){
		(*i)->update();
		if((*i)->getHasPlayed()){
			delete *i;
			i = mAnimationVector.erase(i);
		}else{
			i++;
		}
	}

	finishLine();
	 
	collision();
	killDead();
}

void ActiveLayer::render(){
	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}

	for(std::vector<Animation*>::iterator i = mAnimationVector.begin(); i != mAnimationVector.end(); i++){
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
		if(((*i)->getID() == "Animal" || (*i)->getID() == "Fire")){
			for(EntityVector::iterator j = mEntityVector.begin(); j != mEntityVector.end(); j++){
				if((*i)->getSprite()->getGlobalBounds().intersects((*j)->getSprite()->getGlobalBounds()) && (*i) != (*j)){

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
			if((*i)->getID() == "Animal"){
				mDeadAnimalsVector.push_back((*i)->getFilePath());
				//LevelManager::getInst().getDeadAnimalCollection()->push_back((*i)->getFilePath());
				if(LevelManager::getInst().getDeadAnimalCollection()->size() + mDeadAnimalsVector.size() > 1){
					EventManager::getInst().addEvent("addGameOver");
				}
				
			}
			delete (*i);
			i = mEntityVector.erase(i);
	
		}
		else{
			i++;
		}

	}

}

std::vector<Entity*>* ActiveLayer::getEntityVector(){
	return &mEntityVector;
}

void ActiveLayer::finishLine(){

	mAllAnimalsPassed = true;

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){

		if((*i)->getID() == "Animal"){
			if((*i)->getPos().x < mLevellength){
				mAllAnimalsPassed = false;
			}
		}
	}

	if(mAllAnimalsPassed){
		for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
			if((*i)->getID() == "Animal"){
				mAliveAnimalsVector.push_back((*i)->getFilePath());
			}
		}

		LevelManager::getInst().setDeadAnimals(mDeadAnimalsVector);
		EventManager::getInst().addEvent("addLevelFinished");

	}

} 

void ActiveLayer::addAnimationEffekt(Animation* animation){
	mAnimationVector.push_back(animation);
}

