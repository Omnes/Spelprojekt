#include "Camera.h"
#include "WindowManager.h"
#include "ActiveLayer.h"
#include "LevelManager.h"
#include "ScrollDetector.h"



Camera::Camera(LayerManager* layermanager) : 
	mLayerManager(layermanager), 
	mWindow(WindowManager::getInst().getWindow()), 
	mVelocity(0.0),
	mView(sf::FloatRect(0,0,1280,720)),
	mPosition(mView.getSize().x/2), 
	mMaxVelocity(2.5), 
	mMinVelocity(1),
	mMaxPos(1),
	mMinPos(2000){

		mLevellength=LevelManager::getInst().getLevelLength();
		
}

Camera::~Camera(){

}

void Camera::getMinMax(){
	std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
	mMaxPos = INT_MIN;
	mMinPos = INT_MAX;

	for(std::vector<Entity*>::iterator i = entityVector->begin(); i != entityVector->end(); i++){
		
		if((*i)->getID() == "Animal" ||(*i)->getID() == "Fire"){
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

	getMinMax();

	float panSpeed = 0.1;
	float lastPosition = mPosition;

	if((ScrollDetector::getScrollDelta() > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && mVelocity < mMaxVelocity){

		mVelocity += panSpeed;
	}
	 
	else if((ScrollDetector::getScrollDelta() < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && mVelocity > -mMinVelocity){

		mVelocity -= panSpeed;
	}


	
	if(mPosition > mMaxPos + 320){ 
		mPosition -= 1;
		if (mVelocity > .5){
			mVelocity-= panSpeed*2;
		}
	}	
	
	if(mPosition < mMinPos + 440){
		if (mVelocity < 0){
			mVelocity = 0;
		}
		mPosition = mMinPos + 440;
	}
	 
	if(mPosition<mView.getSize().x - mView.getSize().x/2){
		
		mPosition = mView.getSize().x - mView.getSize().x/2;
	}
	
	if(mPosition > mLevellength - (mView.getSize().x - mView.getSize().x/2)){
		
		mPosition = mLevellength - (mView.getSize().x - mView.getSize().x/2);
	}

	mPosition += mVelocity;

	mLayerManager->move(mPosition-lastPosition);

	mView.setCenter(mPosition, mWindow->getSize().y/2);

	mWindow->setView(mView);

	LevelManager::getInst().setCamera(this);
}

float Camera::getMax(){
	return mMaxPos;
}

sf::View* Camera::getView(){
	return &mView;
}