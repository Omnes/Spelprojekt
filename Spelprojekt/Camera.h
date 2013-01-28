#ifndef CAMERA
#define CAMERA
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include "LayerManager.h"


class Camera{

public:

	Camera(LayerManager* layermanager);
	~Camera();
	void update();

private:

	sf::View mView;
	sf::RenderWindow* mWindow;
	float mVelocity, mPosition, mMaxVelocity, mMinVelocity;
	LayerManager* mLayerManager;
};


#endif