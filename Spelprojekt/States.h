#ifndef STATES
#define STATES

class States{

public:

	virtual void update()=0;
	virtual void render()=0;
	virtual ~States(){};

};

#endif 
