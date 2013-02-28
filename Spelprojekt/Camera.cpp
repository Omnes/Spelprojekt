#include "Camera.h"
#include "WindowManager.h"
#include "ActiveLayer.h"
#include "LevelManager.h"
#include "ScrollDetector.h"
#include "tinyxml2.h"



Camera::Camera(LayerManager* layermanager) : 
	mLayerManager(layermanager), 
	mWindow(WindowManager::getInst().getWindow()), 
	mVelocity(0.0),
	mView(sf::FloatRect(0,0,1280,720)),
	mMaxPos(1),
	mMinPos(2000){

		tinyxml2::XMLDocument doc;
		doc.LoadFile("Resources/data/settings.xml");

		const tinyxml2::XMLAttribute* attr = doc.FirstChildElement("Camera")->FirstAttribute();

		mMinVelocity = attr->FloatValue();
		attr = attr->Next();
		mMaxVelocity = attr->FloatValue(); 
		attr = attr->Next();
		mPanSpeed = attr->FloatValue();

		mLevellength=LevelManager::getInst().getLevelLength();

		float zoomfactor = 1280 / WindowManager::getInst().getWindow()->getSize().x;
		mView.setSize(WindowManager::getInst().getWindow()->getSize().x,WindowManager::getInst().getWindow()->getSize().y);
		mView.zoom(zoomfactor);

		mPosition = mView.getSize().x/2;

}

Camera::~Camera(){

}

void Camera::getMinMax(){
	std::vector<Entity*>* entityVector = LevelManager::getInst().getActiveLayer()->getEntityVector();
	mMaxPos = -1000;
	mMinPos = 1000;

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

	//mView.rotate(1);
	
	

	getMinMax();

	///mView.setSize(mMaxPos-mMinPos,mMaxPos-mMinPos);

	float mPanSpeed = 0.5;
	float lastPosition = mPosition;

	if((ScrollDetector::getScrollDelta() > 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && mVelocity < mMaxVelocity){

		mVelocity += mPanSpeed;
	}
	 
	else if((ScrollDetector::getScrollDelta() < 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && mVelocity > mMinVelocity){

		mVelocity -= mPanSpeed;
	}


	
	if(mPosition > mMaxPos + 320){ 
		mPosition -= 1;
		if (mVelocity > .5){
			mVelocity-= mPanSpeed*2;
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