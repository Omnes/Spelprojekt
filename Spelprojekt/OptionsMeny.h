#ifndef OPTIONSMENY
#define OPTIONSMENY
#include "Button.h"
#include "States.h"

class OptionsMeny: public States{
public:
	virtual void update();
	virtual void render();
	OptionsMeny();
	~OptionsMeny();

	std::string getMusic();

private:
	std::vector<Button*> mButtons;
	std::string mMusic;
	
};


#endif