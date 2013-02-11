#ifndef TACTICALVISION
#define TACTICALVISION
#include "States.h"
#include <SFML\System\Clock.hpp>

class TacticalVision : public States{

public:

	TacticalVision();
	~TacticalVision();
	virtual void update();
	virtual void render();

private:
	States* mRenderState;
	sf::Clock mTimer;

};

#endif