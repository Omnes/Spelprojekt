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

	std::string getMusic();

private:
	Gui mGui;
	Camera *mCamera;
	LayerManager *mLayerManager;
	std::string mMusic;

};


#endif