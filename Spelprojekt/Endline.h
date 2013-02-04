#ifndef ENDLINE
#define ENDLINE
#include "Entity.h"

class Endline : public Entity {

public:
	Endline(sf::Vector2f position);
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
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
};

#endif