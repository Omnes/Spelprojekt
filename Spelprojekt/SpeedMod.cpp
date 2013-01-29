#include "SpeedMod.h"


SpeedMod::SpeedMod(float time, float mod, std::string ID) : 
	mAliveTime(time),
	mMod(mod),
	mID(ID)
{
	mclock.restart();
}

SpeedMod::~SpeedMod(){}

bool SpeedMod::getAlive(){
	return mclock.getElapsedTime().asSeconds() > mAliveTime;
}

float SpeedMod::getMod(){

	return mMod;
}

std::string SpeedMod::getID(){
	return mID;
}