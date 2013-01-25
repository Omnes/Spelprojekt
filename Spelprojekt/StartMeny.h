#ifndef STARTMENY
#define STARTMENY
#include "Button.h"

class StartMeny: public States{
public:
	virtual void update();
	virtual void render();'
	StartMeny();
	~StartMeny();

private:
	std::vector<Button*> mButtons;
	
};


#endif