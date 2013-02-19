#ifndef STATES
#define STATES

#include <string>

class States{

public:

	virtual void update()=0;
	virtual void render()=0;
	virtual ~States(){};
	virtual std::string getMusic()=0;

};

#endif 
