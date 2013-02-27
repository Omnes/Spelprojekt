#ifndef TACTICALVISION
#define TACTICALVISION
#include "States.h"
#include "TacticalVisionCamera.h"
#include <SFML\System\Clock.hpp>
#include "Gameplay.h"
#include "FakeAbilityButton.h"

class TacticalVision : public States{

public:

	TacticalVision();
	~TacticalVision();
	virtual void update();
	virtual void render();
	void readFromFile();
	std::string getMusic();

private:
	Gameplay* mRenderState;
	sf::Clock mTimer;
	TacticalVisionCamera* mCamera;
	float mDuration;
	std::string mMusic;
	typedef std::vector <FakeAbilityButton*> AbilityButton;
	AbilityButton mAbilityButtons;
};

#endif