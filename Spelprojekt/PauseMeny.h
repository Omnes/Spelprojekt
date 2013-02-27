#ifndef PAUSEMENY
#define PAUSEMENY
#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Button.h"
#include "FakeAbilityButton.h"


class PauseMeny: public States{
public:
	PauseMeny();
	~PauseMeny();

	void render();
	void update();
	void readFromFile();

	std::string getMusic();


private:
	States* mRenderState;
	sf::Sprite mSprite;
	Button mResumeButton;
	std::string mMusic;
	typedef std::vector <FakeAbilityButton*> AbilityButton;
	AbilityButton mAbilityButtons;
};

#endif