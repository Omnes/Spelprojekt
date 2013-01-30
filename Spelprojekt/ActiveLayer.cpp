#include "ActiveLayer.h"
#include "Entity.h"
#include "WindowManager.h"
#include <iostream>

ActiveLayer::ActiveLayer(std::vector <Entity*> entityVector):
	mEntityVector(entityVector)
{
	if(mEntityVector.empty()){
		std::cout<<"EntityVector is empty";
	}
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
}

void ActiveLayer::render(){
	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}
}

void ActiveLayer::collision(){

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		
		for(EntityVector::iterator j = mEntityVector.begin(); j != mEntityVector.end(); j++){
	
			if((*i)->getSprite()->getGlobalBounds().intersects((*j)->getSprite()->getGlobalBounds()) && (*i)->getID() != (*j)->getID()){
				
				std::cout<<(*i)->getID()<<"X  "<<(*i)->getPos().x<<std::endl;
				std::cout<<(*i)->getID()<<"Y  "<<(*i)->getPos().y<<std::endl<<std::endl;

				std::cout<<(*j)->getID()<<"X  "<<(*j)->getPos().x<<std::endl;
				std::cout<<(*j)->getID()<<"Y  "<<(*j)->getPos().y<<std::endl<<std::endl;

				(*i)->collide((*j));
				(*j)->collide((*i));
			}	
		}
	}
}

void ActiveLayer::checkAlive(){

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end();){

		if((*i)->getAlive() == false){
			//delete (*i);    <<----------------------------------- TA BORT SAKER MED DE HÄR RADERNA 
			//i = mEntityVector.erase(i);
		}else{
			i++;
		}

	}

}