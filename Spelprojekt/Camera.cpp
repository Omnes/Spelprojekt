#include "Camera.h"
#include "WindowManager.h"


Camera::Camera(LayerManager* layermanager) : mLayerManager(layermanager), mWindow(WindowManager::getInst().getWindow()), mVelocity(0.0), mView(sf::FloatRect(0,0,600,600)), mPosition(300), mMaxVelocity(1){

	
}

Camera::~Camera(){

}

void Camera::update(){

	float panSpeed = 0.001;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mVelocity<mMaxVelocity){

		mVelocity+=panSpeed;
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mVelocity>-1){

		mVelocity-=panSpeed;
	}

	mPosition+=mVelocity;

	mView.setCenter(mPosition, mWindow->getSize().y/2);

	mWindow->setView(mView);

	mLayerManager->move(mVelocity);
	
}

