#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>

class Behavior;

struct Particle{
public:

	Particle();
	~Particle();

	void update();
	const sf::Sprite& getSprite()const;

	sf::Sprite mSprite;
	int mLife;
	float mSpeed;
	float mSpeedIncrease;
	sf::Vector2f mDirection;
	sf::Vector2f mPosition;

	float mColorR;
	float mColorG;
	float mColorB;
	float mColorA;
	float mColorChangeR;
	float mColorChangeG;
	float mColorChangeB;
	float mColorChangeA;

	float mRotation;
	float mRotationIncrease;
	float mScale;
	float mScaleIncrease;

	Behavior* mBehavior;

};

#endif
