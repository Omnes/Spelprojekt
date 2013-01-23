#ifndef EVENTMANAGER
#define EVENTMANAGER

#include "Event.h"

#include <string>
#include <stack>
#include <map>
#include <iostream>

class EventManager{
public:
	~EventManager();
	static EventManager& getInst();
	void addEvent(std::string eventName);
	void update();

private:
	EventManager();
	EventManager(const EventManager&);
	EventManager& operator=(const EventManager&);

	typedef std::stack <Event*> EventStack;
	EventStack mEventStack;

	typedef std::map <std::string, Event*> EventMap;
	EventMap mEventMap;
};

#endif