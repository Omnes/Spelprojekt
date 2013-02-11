#ifndef OBSTACLE
#define OBSTACLE
#include "Entity.h"
#include <SFML\Graphics\Texture.hpp>


class Obstacle : public Entity{

public:

	Obstacle(sf::Texture* texture, sf::Vector2f position, float speed, std::string ID);
	~Obstacle();
	virtual void update();
	virtual sf::Sprite* getSprite();
	virtual sf::FloatRect* getRect();
	virtual bool getAlive();
	virtual void setAlive(bool alive);
	virtual void collide(Entity* entity);
	std::string getID();
	
	virtual sf::Vector2f getPos();
	virtual float doDamage();

private:

	std::string mID;
	sf::Texture* mTexture;
	sf::Vector2f mPosition;
	float mSpeedEffect;
	sf::Sprite mSprite;
	bool mAlive;
	sf::Clock collideCooldown;
};

#endif