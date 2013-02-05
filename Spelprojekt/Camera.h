#ifndef CAMERA
#define CAMERA
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include "LayerManager.h"
#include "Entity.h"

class Camera{

public:

	Camera(LayerManager* layermanager);
	~Camera();
	void update();
	void namnsenare();
	float getMax();


private:
	
	int mLevellength;
	sf::View mView;
	sf::RenderWindow* mWindow;
	float mVelocity, mPosition, mMaxVelocity, mMinVelocity, mMaxPos, mMinPos;
	LayerManager* mLayerManager;
};


#endif