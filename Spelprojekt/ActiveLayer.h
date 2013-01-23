#ifndef ACTIVELAYER
#define ACTIVELAYER

//subklass till layer
#include "Layer.h"

//det här är entityManager
class Entity;

#include <iostream>
#include <vector>

//utritning
class WindowManager;

class ActiveLayer : public Layer{
public:
	ActiveLayer(std::vector <Entity*> entityVector);
	void move(float velocity);
	void update();
	void render();

	//extra funktioner utanför basklassen layer
	//fungerar som EntityManager
	void collision();
	void checkAlive();
	~ActiveLayer();
private:
	typedef std::vector<Entity*> EntityVector;
	EntityVector mEntityVector;

};

#endif