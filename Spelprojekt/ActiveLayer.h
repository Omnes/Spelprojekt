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
class Camera;

class ActiveLayer : public Layer{
public:
	ActiveLayer(std::vector <Entity*> entityVector, int levellength);
	~ActiveLayer();
	
	void move(float velocity);
	void update();
	void render();

	//extra funktioner utanför basklassen layer
	//fungerar som EntityManager
	void collision();
	void killDead();
	void finishLine();
	std::vector<Entity*>* getEntityVector();

private:
	typedef std::vector<Entity*> EntityVector;
	EntityVector mEntityVector;
	bool mAllAnimalsPassed;
	int mLevellength;
	std::vector<std::string>mAliveAnimalsVector, mDeadAnimalsVector;
	Camera* mThisCamera;
	
};

#endif