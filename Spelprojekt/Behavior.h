#pragma once
struct Particle;

//a baseclass to add functionality to some particles
class Behavior{
public:
	virtual void update(Particle* particle) = 0;
	virtual ~Behavior(){};
	Behavior(){};
private:
	
};

