#include "ParticlePrototype.h"
#include "Particle.h"
#include <SFML\Graphics\Texture.hpp>
#include "Behavior.h"

static sf::Texture TextureNotFound;

void ParticlePrototype::init(){
	TextureNotFound.loadFromFile("resources/fileNotFound.png");
}

ParticlePrototype::ParticlePrototype(){
	mTexture = &TextureNotFound;

	mBehavior = 0;

	mYFrames = 1;

	mSpeedMin = 0;
	mSpeedMax = 0;
	mSpeedIncrease = 0;

	mDirectionMin = 0;
	mDirectionMax = 0;
	
	mLifeMin = -3;
	mLifeMax = -2;

	mColorMin = sf::Color(255,255,255,255);
	mColorMax = sf::Color(255,255,255,255);
	mColorEndMin = sf::Color(0,0,0,0);
	mColorEndMax = sf::Color(0,0,0,0);

	mScaleMin = 0;
	mScaleMax = 0;
	mScaleIncrease = 0;

	mRotationMin = 0;
	mRotationMax = 0;
	mRotationIncreaseMin = 0;
	mRotationIncreaseMax = 0;

}


ParticlePrototype::~ParticlePrototype(){
	if(mBehavior!=0)
		delete mBehavior;
}


void ParticlePrototype::setTexture(sf::Texture* texture, int yframes){
	mTexture = texture;
	mYFrames = yframes;
}

void ParticlePrototype::setSpeed(float speedMin,float speedMax,float speedIncrease){
	mSpeedMin = speedMin;
	mSpeedMax = speedMax;
	mSpeedIncrease = speedIncrease;
}

void ParticlePrototype::setDirection(float directionMin,float directionMax){
	mDirectionMin = directionMin;
	mDirectionMax = directionMax;
}

void ParticlePrototype::setLife(int lifeMin,int lifeMax){
	mLifeMin = lifeMin;
	mLifeMax = lifeMax;
}

void ParticlePrototype::setScale(float scaleMin,float scaleMax,float scaleIncrease){
	mScaleMin = scaleMin;
	mScaleMax = scaleMax;
	mScaleIncrease = scaleIncrease;
}

void ParticlePrototype::setRotation(float rotationMin,float rotationMax, float rotationIncreaseMin,float rotationIncreaseMax){
	mRotationMin = rotationMin;
	mRotationMax = rotationMax;
	mRotationIncreaseMin = rotationIncreaseMin;
	mRotationIncreaseMax = rotationIncreaseMax;
}

void ParticlePrototype::setColor(sf::Color colorMin, sf::Color colorMax, sf::Color colorEndMin, sf::Color colorEndMax){
	mColorMin = colorMin;
	mColorMax = colorMax;
	mColorEndMin = colorEndMin;
	mColorEndMax = colorEndMax;
}

void ParticlePrototype::setColor(sf::Color color, sf::Color colorEnd){
	mColorMin = color;
	mColorMax = color;
	mColorEndMin = colorEnd;
	mColorEndMax = colorEnd;

}

void ParticlePrototype::setBehavior(Behavior* behavior){
	mBehavior = behavior;
}


float randRangef(float min, float max){
	if (min == max) return min;
	return min +(float) rand() / ((float) RAND_MAX / (max - min));
}

int randRangei(int min, int max){
	if (min == max) return min;
	return min + rand() % (max - min);
}

void ParticlePrototype::setValuesOn(Particle& particle){

	particle.mSprite.setTexture(*mTexture);
	particle.mSprite.setTextureRect(sf::IntRect(0,(mTexture->getSize().y/mYFrames)*(rand()%mYFrames),mTexture->getSize().x,mTexture->getSize().y/mYFrames));
	particle.mSprite.setOrigin(particle.mSprite.getLocalBounds().width/2,particle.mSprite.getLocalBounds().height/2);

	particle.mSpeed = randRangef(mSpeedMin, mSpeedMax);
	particle.mSpeedIncrease = mSpeedIncrease;

	float dir = randRangef(mDirectionMin, mDirectionMax);
	particle.mDirection = sf::Vector2f(std::cos(dir * 3.14f / 180), -std::sin(dir * 3.14f / 180));
	
	particle.mLife = randRangei(mLifeMin, mLifeMax);

	particle.mScale = randRangef(mScaleMin, mScaleMax);
	particle.mScaleIncrease = mScaleIncrease;

	particle.mRotation = randRangef(mRotationMin, mRotationMax);
	particle.mRotationIncrease = randRangef(mRotationIncreaseMin, mRotationIncreaseMax);

	sf::Color color;
	color.r = randRangei(mColorMin.r,mColorMax.r);
	color.g = randRangei(mColorMin.g,mColorMax.g);
	color.b = randRangei(mColorMin.b,mColorMax.b);
	color.a = randRangei(mColorMin.a,mColorMax.a);

	particle.mColorR = color.r;
	particle.mColorG = color.g;
	particle.mColorB = color.b;
	particle.mColorA = color.a;

	sf::Color colorEnd;
	colorEnd.r = randRangei(mColorEndMin.r,mColorEndMax.r);
	colorEnd.g = randRangei(mColorEndMin.g,mColorEndMax.g);
	colorEnd.b = randRangei(mColorEndMin.b,mColorEndMax.b);
	colorEnd.a = randRangei(mColorEndMin.a,mColorEndMax.a);

	sf::Color colorIncrease;
	int lt = particle.mLife;
	particle.mColorChangeR = (float)(colorEnd.r - color.r)/lt;
	particle.mColorChangeG = (float)(colorEnd.g - color.g)/lt;
	particle.mColorChangeB = (float)(colorEnd.b - color.b)/lt; 
	particle.mColorChangeA = (float)(colorEnd.a - color.a)/lt;

	particle.mBehavior = mBehavior;

}
