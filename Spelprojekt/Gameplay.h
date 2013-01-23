#ifndef GAMEPLAY
#define GAMEPLAY
#include "States.h"
#include "Camera.h"
#include "LayerManager.h"
//#include "GUI.h"

class Gameplay : public States{
	 
public:

	Gameplay();
	~Gameplay();
	virtual void update();
	virtual void render();

private:

	Camera mCamera;
	LayerManager mLayerManager;

};


#endif