#ifndef OPTIONSMENU
#define OPTIONSMENU
#include "States.h"

class OptionsMeny : public States{

public:

	OptionsMeny();
	~OptionsMeny();
	virtual void update();
	virtual void render();

};

#endif