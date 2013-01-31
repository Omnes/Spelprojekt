#include "Camera.h"
#include "WindowManager.h"


Camera::Camera(LayerManager* layermanager) : 
	mLayerManager(layermanager), 
	mWindow(WindowManager::getInst().getWindow()), 
	mVelocity(0.0), 
	mView(sf::FloatRect(0,0,1280,720)),
	mPosition(mView.getSize().x/2), 
	mMaxVelocity(1), 
	mMinVelocity(1){

	
}

Camera::~Camera(){

}

void Camera::update(){

	float panSpeed = 0.01;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mVelocity<mMaxVelocity){

		mVelocity+=panSpeed;
	}
	 
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mVelocity>-mMinVelocity){

		mVelocity-=panSpeed;
	}

	mPosition+=mVelocity;

	mView.setCenter(mPosition, mWindow->getSize().y/2);

	mWindow->setView(mView);

	mLayerManager->move(mVelocity);
	
	
}

