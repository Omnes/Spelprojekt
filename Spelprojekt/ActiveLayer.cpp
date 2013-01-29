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

}

void ActiveLayer::update(){
	collision();
	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		(*i)->update();
	}
}

void ActiveLayer::render(){
	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		WindowManager::getInst().getWindow()->draw(*(*i)->getSprite());
	}
}

void ActiveLayer::collision(){

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		sf::FloatRect iRect = *(*i)->getRect();
		
		for(EntityVector::iterator j = mEntityVector.begin(); j != mEntityVector.end(); j++){
		sf::FloatRect jRect = *(*j)->getRect(); // <-----------------------------------------------------ta bort sen ???
	
			if(iRect.intersects(jRect)){
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