#include "SpeedMod.h"


SpeedMod::SpeedMod(float time, float mod): mAliveTime(time), mMod(mod){
	clock.restart();
}

SpeedMod::~SpeedMod(){}

bool SpeedMod::getAlive(){
	return clock.getElapsedTime().asSeconds() > mAliveTime;
}

float SpeedMod::getMod(){

	return mMod;
}


