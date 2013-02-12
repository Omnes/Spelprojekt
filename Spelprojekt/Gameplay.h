#ifndef GAMEPLAY
#define GAMEPLAY
#include "States.h"
#include "Camera.h"
#include "LayerManager.h"
#include "Gui.h"

class Gameplay : public States{
	 
public:

	Gameplay();
	~Gameplay();
	virtual void update();
	virtual void render();
	void renderFromTacVision();
	LayerManager* getLayerManager();

private:
	Gui mGui;
	Camera *mCamera;
	LayerManager *mLayerManager;

};


#endif