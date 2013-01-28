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
}

void ActiveLayer::update(){
	std::cout << "heuuhe";
	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		(*i)->update();
	}
}

void ActiveLayer::render(){
	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		WindowManager::getInst().getWindow()->draw((*i)->getSprite());
	}
}

void ActiveLayer::collision(){

//void EntityManager::collision(){
//
//for(EntityVector::iterator i = d_eVector.begin(); i != d_eVector.end(); i++){
//	sf::FloatRect iRect = (*i)->getRect();
//	
//	for(EntityVector::iterator j = d_eVector.begin(); j != d_eVector.end(); j++){
//	sf::FloatRect jRect = (*j)->getRect();
//	
//		if((*i)->getCat() != (*j)->getCat() && iRect.intersects(jRect)){
//			(*i)->collide((*j));
//			(*j)->collide((*i));
//			}	
//		}
//	}
//}

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end(); i++){
		for(EntityVector::iterator j = mEntityVector.begin(); j != mEntityVector.end(); j++){
			if((*i)->getRect().intersects((*j)->getRect())){
					std::cout<<"HIT IS HIT"<<std::endl;
			}	
		}
	}

}

void ActiveLayer::checkAlive(){

	for(EntityVector::iterator i = mEntityVector.begin(); i != mEntityVector.end();){

		if((*i)->getAlive() == false){
			delete (*i);
			i = mEntityVector.erase(i);
		}else{
			i++;
		}

	}

}