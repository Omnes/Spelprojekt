#ifndef STARTMENY
#define STARTMENY
#include "Button.h"
#include "States.h"

class StartMeny: public States{
public:
	virtual void update();
	virtual void render();
	StartMeny();
	~StartMeny();

private:
	std::vector<Button*> mButtons;
	
};


#endif