#ifndef PARTICLEPROTOTYPE_H
#define PARTICLEPROTOTYPE_H
#include <SFML\Graphics\Color.hpp>

//#include "Particle.h"

namespace sf{
	class Texture;
}

class Behavior;
struct Particle;

class ParticlePrototype{
public:

	ParticlePrototype();
	~ParticlePrototype();
	static void init();

	void setTexture(sf::Texture* texture,int yframes);

	void setSpeed(float speedMin,float speedMax,float speedIncrease);

	void setDirection(float directionMin,float directionMax);

	void setLife(int lifeMin,int lifeMax);

	void setScale(float scaleMin,float scaleMax,float scaleIncrease);

	void setRotation(float rotationMin,float rotationMax, float rotationIncreaseMin,float rotationIncreaseMax);

	void setValuesOn(Particle& particle);

	void setColor(sf::Color colorMin, sf::Color colorMax, sf::Color colorEndMin, sf::Color colorEndMax);
	void setColor(sf::Color color,sf::Color colorEnd);

	void setBehavior(Behavior* behavior);


private:

	sf::Texture* mTexture;
	int mYFrames;

	float mSpeedMin;
	float mSpeedMax;
	float mSpeedIncrease;

	float mDirectionMin;
	float mDirectionMax;
	
	int mLifeMin;
	int mLifeMax;

	sf::Color mColorMin;
	sf::Color mColorMax;
	sf::Color mColorEndMin;
	sf::Color mColorEndMax;

	float mScaleMin;
	float mScaleMax;
	float mScaleIncrease;

	float mRotationMin;
	float mRotationMax;
	float mRotationIncreaseMin;
	float mRotationIncreaseMax;

	Behavior* mBehavior;



};

#endif