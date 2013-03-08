#ifndef OPTIONSMENY
#define OPTIONSMENY
#include "Button.h"
#include "States.h"
#include "Checkbox.h"
#include "ApplyOptionsButton.h"
#include "OptionSlider.h"

class ResourceManager;

class OptionsMeny: public States{
public:
	virtual void update();
	virtual void render();
	OptionsMeny();
	~OptionsMeny();
	void saveSettings();

	std::string getMusic();

private:
	std::vector<Checkbox*> mCheckboxes;

	typedef std::vector<OptionSlider*> OptionSliders;
	OptionSliders mOptionSliders;

	//OptionSlider* mOptionSlider;

	ApplyOptionsButton mApplyButton;

	std::string mMusic;

	sf::Sprite mBackground;
	
};


#endif