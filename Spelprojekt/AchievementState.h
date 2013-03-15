#ifndef ACHIEVEMENTSTATE
#define ACHIEVEMENTSTATE
#include "States.h"
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Window\Keyboard.hpp>
#include "tinyxml2.h"
#include "Button.h"
#include <vector>



class AchievementState : public States{

public:
	AchievementState(int section);
	~AchievementState(); 
	virtual void update();
	virtual void render();
	virtual std::string getMusic();

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

	Button* mButton;

	float mTutorialDuration;

};



#endif