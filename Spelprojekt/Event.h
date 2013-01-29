#ifndef EVENT
#define EVENT

class Event{
public:
	virtual ~Event(){};
	virtual void update()=0;
};

#endif