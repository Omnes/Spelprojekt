#ifndef ENDLINE
#define ENDLINE
#include "Entity.h"
#include <SFML\Graphics\Texture.hpp>

class Endline : public Entity {

public:
	Endline(sf::Vector2f position, sf::Texture *texture);
	~Endline();
	virtual void update();
	virtual sf::FloatRect* getRect();
	virtual sf::Sprite* getSprite();
	virtual bool getAlive();
	virtual void setAlive(bool alive);
	virtual void collide(Entity* entity);
	virtual void setMod(SpeedMod* speedMod);
	virtual std::string getID();
	virtual sf::Vector2f getPos();

private:
	std::string mID;
	sf::IntRect mRectangle;
	sf::Sprite* mSprite;
	sf::Texture* mTexture;
};

#endif