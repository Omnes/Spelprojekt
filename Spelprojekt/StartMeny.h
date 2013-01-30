#ifndef STARTMENY
#define STARTMENY
#include "Button.h"
#include "States.h"

class StartMeny: public States{
public:
	virtual void update();
	virtual void render();
	StartMeny();
	States* createNew();
	~StartMeny();

private:
	std::vector<Button*> mButtons;
	
};


#endif