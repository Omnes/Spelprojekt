#ifndef LAYER
#define LAYER

class Layer{
public:
	virtual ~Layer(){}
	virtual void update()=0;
	virtual void render()=0;
	virtual void move(float velocity)=0;
};

#endif