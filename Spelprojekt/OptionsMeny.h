#ifndef OPTIONSMENY
#define OPTIONSMENY
#include "Button.h"
#include "States.h"

class OptionsMeny: public States{
public:
	virtual void update();
	virtual void render();
	States* createNew();
	OptionsMeny();
	~OptionsMeny();

private:
	std::vector<Button*> mButtons;
	
};


#endif