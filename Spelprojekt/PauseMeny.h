#ifndef PAUSEMENY
#define PAUSEMENY
#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Button.h"


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
	Button mResumeButton;
};

#endif