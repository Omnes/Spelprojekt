#ifndef EXITGAME
#define EXITGAME
#include "Event.h"
#include "WindowManager.h"

class ExitGame : public Event{

public:

	ExitGame(){}
	~ExitGame(){}
	virtual void update(){ WindowManager::getInst().getWindow()->close(); }
};

#endif