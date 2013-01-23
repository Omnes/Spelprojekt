#include "LayerManager.h"
#include "Layer.h"
#include "LevelManager.h"
#include <iostream>

LayerManager::LayerManager(): 
	mLayerVector(LevelManager::getInst().loadLayers())           // <-------------ändra den här
{}

LayerManager::~LayerManager(){

}

void LayerManager::move(float velocity){
	for(LayerVector::iterator i = mLayerVector.begin(); i != mLayerVector.end(); i++){
		(*i)->move(velocity);
	}
}

void LayerManager::update(){
	for(LayerVector::iterator i = mLayerVector.begin(); i != mLayerVector.end(); i++){
		(*i)->update();
	}
}

void LayerManager::render(){
	for(LayerVector::iterator i = mLayerVector.begin(); i != mLayerVector.end(); i++){
		(*i)->render();
	}
}