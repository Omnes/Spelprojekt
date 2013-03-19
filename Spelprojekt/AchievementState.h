#ifndef ACHIEVEMENTSTATE
#define ACHIEVEMENTSTATE
#include "States.h"
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "tinyxml2.h"
#include "Button.h"
#include <vector>
#include "ParticleManager.h"
#include "EventManager.h"



class AchievementState : public States{

public:
	AchievementState(int section);
	~AchievementState(); 
	virtual void update();
	virtual void render();
	virtual std::string getMusic();
	void saveUnlocked();

private:

	std::string mMusic;
	States* mPreState;
	sf::Sprite mSprite;
	sf::Clock mTimer;

	int mSection;

	typedef std::vector <std::string> AnimalVector;
	AnimalVector mAnimalVector;

	typedef std::vector <sf::Sprite*> ImageVector;
	ImageVector mImageVector;

	typedef std::vector <std::string> UnlockVector;
	UnlockVector mUnlockVector;

	Button* mButton;

	float mTutorialDuration;

};



#endif