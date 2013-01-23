#include "StaticLayer.h"
#include "WindowManager.h"

StaticLayer::StaticLayer(std::vector <sf::Sprite*> spriteVector ,float layerVelocity):
	mConstVelocity(layerVelocity),
	mSpriteVector(spriteVector)
{
	if(mSpriteVector.empty()){
		std::cout<<"SpriteVector is empty";
	}
	//om inget funkar! testa detta ;)
	//mSpriteVector.at(0)->setPosition(0,0);
}

StaticLayer::~StaticLayer(){}

void StaticLayer::move(float cameraVelocity){

	//exception för första bilden. 
	for(SpriteVector::size_type i = 1; i < mSpriteVector.size(); i++){
		mSpriteVector.at(i)->setPosition((mSpriteVector.at(i-1)->getPosition().x + mSpriteVector.at(i-1)->getGlobalBounds().width) + mConstVelocity * cameraVelocity, 0);
	}
}

void StaticLayer::update(){

}

void StaticLayer::render(){
	for(SpriteVector::iterator i = mSpriteVector.begin(); i != mSpriteVector.end(); i++){
		//om något är fel kanske ändra denna ??
		WindowManager::getInst().getWindow()->draw(*(*i));
	}
}