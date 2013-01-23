#ifndef LAYERMANAGER
#define LAYERMANAGER

class Layer;
class LevelManager;

#include <vector>

//inte inkluderat Layer.h än
//tar hand om alla layers. även ActiveLayer(EntityManager. konstigt ? perhaps)

class LayerManager{
public:
	LayerManager(); //lägg till vectorn med layers från LevelManager här    <-----------------
	~LayerManager();
	void move(float velocity);
	void update();
	void render();


private:
	typedef std::vector <Layer*> LayerVector;
	LayerVector mLayerVector;
};

#endif