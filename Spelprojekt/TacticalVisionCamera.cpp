#include "TacticalVisionCamera.h"
#include "WindowManager.h"
#include "ActiveLayer.h"
#include "LevelManager.h"
#include "Camera.h"

TacticalVisionCamera::TacticalVisionCamera(LayerManager* layermanager) : 
	mLayerManager(layermanager), 
	mWindow(WindowManager::getInst().getWindow()), 
	mVelocity(0.0),
	mView(*LevelManager::getInst().getCamera()->getView()),
	mPosition(mView.getCenter().x), 
	mMaxVelocity(2.5), 
	mMinVelocity(1),
	mMinPos(2000),
	mStartPosition(mView.getCenter().x){

		mLevellength=LevelManager::getInst().getLevelLength();
		
}

TacticalVisionCamera::~TacticalVisionCamera(){

}

void TacticalVisionCamera::setMin(){
	std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
	mMinPos = INT_MAX;

	for(std::vector<Entity*>::iterator i = entityVector->begin(); i != entityVector->end(); i++){
		
		if((*i)->getID() == "Fire" && (*i)->getPos().x < mMinPos){

				mMinPos=(*i)->getPos().x;
		}
	}
}

void TacticalVisionCamera::update(){

	setMin();

	float panSpeed = 0.1;
	float lastPosition = mPosition;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mVelocity < mMaxVelocity){

		mVelocity += panSpeed;
	}
	 
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mVelocity > -mMinVelocity){

		mVelocity -= panSpeed;
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

}

void TacticalVisionCamera::moveBackToStartPosition(){

	float lastPosition = mPosition;

	mPosition += (mStartPosition-mPosition)/10;

	mLayerManager->move(mPosition-lastPosition);//<<<<<<<<<<<<<<<<<<<<<--------------------------------------------kan göras snyggare

	mView.setCenter(mPosition, mWindow->getSize().y/2);

	mWindow->setView(mView);

}

sf::View* TacticalVisionCamera::getView(){
	return &mView;
}