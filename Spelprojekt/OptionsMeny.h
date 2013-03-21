#ifndef OPTIONSMENY
#define OPTIONSMENY
#include "Button.h"
#include "States.h"
#include "Checkbox.h"
#include "ApplyOptionsButton.h"
#include "OptionSlider.h"
#include <SFML\Graphics\Text.hpp>
#include "FontMaster.h"


class OptionsMeny: public States{
public:
	virtual void update();
	virtual void render();
	OptionsMeny();
	~OptionsMeny();
	void saveSettings();
	std::string getMusic();
	void readText();

private:
	std::vector<Checkbox*> mCheckboxes;

	typedef std::vector<OptionSlider*> OptionSliders;
	OptionSliders mOptionSliders;

	ApplyOptionsButton mApplyButton;

	std::string mMusic;

	sf::Sprite mBackground;

	sf::Text mText;
	typedef std::vector <sf::Text> OptionText;
	OptionText mOptionText;
	
};


#endif