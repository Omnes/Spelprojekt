#ifndef WAITSTATE
#define WAITSTATE
#include <string>
#include "StateManager.h"
#include "EventManager.h"
#include "States.h"


class WaitState : public States{
public:
	WaitState(std::string evt);
	~WaitState();

	void render();
	void update();

	std::string getMusic();

private:
	std::string mEvent;


};

#endif