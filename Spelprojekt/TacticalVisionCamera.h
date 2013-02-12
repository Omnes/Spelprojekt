#ifndef TACTICALVISIONCAMERA
#define TACTICALVISIONCAMERA
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>
#include "LayerManager.h"
#include "Entity.h"

class TacticalVisionCamera{

public:

	TacticalVisionCamera(LayerManager* layermanager);
	~TacticalVisionCamera();
	void update();
	void setMin();
	sf::View* getView();
	void moveBackToStartPosition();


private:
	
	int mLevellength;
	sf::View mView;
	sf::RenderWindow* mWindow;
	float mVelocity, mPosition, mMaxVelocity, mMinVelocity, mMinPos, mStartPosition;
	LayerManager* mLayerManager;
};


#endif