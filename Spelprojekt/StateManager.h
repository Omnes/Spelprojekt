#ifndef STATEMANAGER
#define STATEMANAGER
#include <string>
#include <stack>
#include <map>
#include "States.h"

class StateManager{

public:

	static StateManager& getInst();
	void addState(States* state);
	void update();
	void popState();
	void render();
	States* getTop();


private:

	void changeMusic();

	typedef std::map<std::string, States*> StateMap;
	StateMap mStateMap;
	std::stack<States*> mStates;
	StateManager();
	StateManager& operator=(const StateManager&);
	StateManager(const StateManager&);
	~StateManager();

};


#endif