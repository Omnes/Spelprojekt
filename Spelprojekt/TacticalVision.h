#ifndef TACTICALVISION
#define TACTICALVISION
#include "States.h"
#include "TacticalVisionCamera.h"
#include <SFML\System\Clock.hpp>
#include "Gameplay.h"

class TacticalVision : public States{

public:

	TacticalVision();
	~TacticalVision();
	virtual void update();
	virtual void render();

private:
	Gameplay* mRenderState;
	sf::Clock mTimer;
	TacticalVisionCamera* mCamera;
	float mDuration;

};

#endif