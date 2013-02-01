#include "Camera.h"
#include "WindowManager.h"
#include "ActiveLayer.h"
#include "LevelManager.h"




Camera::Camera(LayerManager* layermanager) : 
	mLayerManager(layermanager), 
	mWindow(WindowManager::getInst().getWindow()), 
	mVelocity(0.0), 
	mView(sf::FloatRect(0,0,1280,720)),
	mPosition(mView.getSize().x/2), 
	mMaxVelocity(1), 
	mMinVelocity(1),
	mMaxPos(1),
	mMinPos(2000){

		
}

Camera::~Camera(){

}

void Camera::namnsenare(){
	std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
	mMaxPos = INT_MIN;
	mMinPos = INT_MAX;

	for(std::vector<Entity*>::iterator i = entityVector->begin(); i != entityVector->end(); i++){
		
		if((*i)->getID() != "Obstacle"){
			if((*i)->getPos().x > mMaxPos){
				mMaxPos=(*i)->getPos().x;
			}

			if((*i)->getPos().x < mMinPos){
				mMinPos=(*i)->getPos().x;
			}
		}
	}
}

void Camera::update(){

	namnsenare();

	float panSpeed = 0.01;
	float lastPosition = mPosition;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mVelocity<mMaxVelocity){

		mVelocity+=panSpeed;
	}
	 
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mVelocity>-mMinVelocity){

		mVelocity-=panSpeed;
	}

	if(mPosition>mMaxPos){ 
		mPosition=mMaxPos;
	}
	
	if(mPosition<mMinPos){
		mPosition=mMinPos;
	}
	
	mPosition+=mVelocity;

	mLayerManager->move(mPosition-lastPosition);
	
	mView.setCenter(mPosition, mWindow->getSize().y/2);

	mWindow->setView(mView);

	LevelManager::getInst().setCamera(this);
}

float Camera::getMax(){
	return mMaxPos;
}