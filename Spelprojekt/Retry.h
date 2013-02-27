#ifndef RETRY
#define RETRY

#include "Event.h"
#include "StateManager.h"
#include "GameOver.h"
#include "Taktikmeny.h"

class Retry: public Event{
public:
	void update(){
		StateManager::getInst().popState(); 
		GameOver::sRetryCount ++;
		StateManager::getInst().addState(new TaktikMeny);}
	Retry(){}
	~Retry(){}
};



#endif