#include "Gameplay.h"

Gameplay::Gameplay() : 
	mLayerManager(), 
	mCamera(&mLayerManager)
{

}

Gameplay::~Gameplay(){

}

void Gameplay::update(){

	mLayerManager.update();
	mCamera.update();
}

void Gameplay::render(){

	mLayerManager.render();
}

States* Gameplay::createNew(){
	return new Gameplay;
}