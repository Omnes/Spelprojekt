#ifndef OPTIONSMENY
#define OPTIONSMENY
#include "Button.h"
#include "States.h"
#include "Checkbox.h"
#include "ApplyOptionsButton.h"

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
	ApplyOptionsButton mApplyButton;

	std::string mMusic;
	
};


#endif