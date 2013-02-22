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
	void getMinMax();
	float getMax();
	sf::View* getView();


private:
	
	int mLevellength;
	float mPanSpeed;
	sf::View mView;
	sf::RenderWindow* mWindow;
	float mVelocity, mPosition, mMaxVelocity, mMinVelocity, mMaxPos, mMinPos;
	LayerManager* mLayerManager;
};


#endif