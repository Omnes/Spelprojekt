#ifndef FIRE
#define FIRE
#include "Entity.h"
#include <string>
#include "ParticleSystem.h"
#include "Emitter.h"
#include <SFML\System\Clock.hpp>
#include <SFML\Audio\Sound.hpp>

	
class Fire: public Entity{
public:
	Fire(sf::Vector2f position, float speed);
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
	float mCloseupSpeed;
	float mSpeed;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	std::string mID;
	bool mAlive;
	ParticleSystem mSmokeSystem;
	ParticleSystem mFireSystem;
	ParticleSystem mPoofSystem;
	sf::Clock mSpeedUpdateCooldown;
	sf::Sound mDeathSound;
	
	Emitter mEmitter;


};

#endif