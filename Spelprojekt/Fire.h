#ifndef FIRE
#define FIRE
#include "Entity.h"
#include <string>
#include "ParticleSystem.h"
#include "Emitter.h"
	
class Fire: public Entity{
public:
	Fire(sf::Vector2f position, float speed, float acceleration);
	~Fire();

	virtual void update();
	virtual sf::FloatRect* getRect();
	virtual sf::Sprite* getSprite();
	virtual bool getAlive();
	virtual void setAlive(bool alive);
	virtual void collide(Entity* entity);
	virtual std::string getID();
	virtual sf::Vector2f getPos();
	virtual float doDamage();

private:
	float mSpeed;
	float mAcceleration;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	std::string mID;
	bool mAlive;
	ParticleSystem mSmokeSystem;
	ParticleSystem mFireSystem;
	ParticleSystem mPoofSystem;
	
	Emitter mEmitter;


};

#endif