#ifndef TAKTIKMENY
#define TAKTIKMENY

#include "States.h"

class TaktikMeny: States{
public:
	virtual void update();
	virtual void render();
	~TaktikMeny();
	TaktikMeny();

};


#endif