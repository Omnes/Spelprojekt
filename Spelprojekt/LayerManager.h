#ifndef LAYERMANAGER
#define LAYERMANAGER

class Layer;
class LevelManager;

#include <vector>

//inte inkluderat Layer.h �n
//tar hand om alla layers. �ven ActiveLayer(EntityManager. konstigt ? perhaps)

class LayerManager{
public:
	LayerManager(); //l�gg till vectorn med layers fr�n LevelManager h�r    <-----------------
	~LayerManager();
	void move(float velocity);
	void update();
	void render();


private:
	typedef std::vector <Layer*> LayerVector;
	LayerVector mLayerVector;
};

#endif