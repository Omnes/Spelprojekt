#ifndef STATEMANAGER
#define STATEMANAGER
#include <string>
#include <stack>
#include <map>
#include "States.h"

class StateManager{

public:

	static StateManager& getInst();
	void addState(std::string state);
	void update();
	void popState();
	void render();



private:

	typedef std::map<std::string, States*> StateMap;
	StateMap mStateMap;
	std::stack<States*> mStates;
	StateManager();
	StateManager& operator=(const StateManager&);
	StateManager(const StateManager&);
	~StateManager();

};


#endif