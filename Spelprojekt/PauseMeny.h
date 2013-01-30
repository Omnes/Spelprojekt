#ifndef PAUSEMENY
#define PAUSEMENY
#include "States.h"
#include <SFML\Graphics\Sprite.hpp>


class PauseMeny: public States{
public:
	PauseMeny();
	~PauseMeny();

	void render();
	void update();
	States* createNew();


private:
	States* mRenderState;
	sf::Sprite mSprite;
};

#endif