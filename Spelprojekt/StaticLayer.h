#ifndef STATICLAYER
#define STATICLAYER

//subklass till layer
#include "Layer.h"

//utritning
class WindowManager;

//bakgrund
#include <SFML\Graphics\Sprite.hpp>

#include <vector>
#include <iostream>

class StaticLayer : public Layer{
public:
	StaticLayer(std::vector <sf::Sprite*> spriteVector, float velocity);
	void move(float cameraVelocity);
	void update();
	void render();
	~StaticLayer();
private:
	
	
	typedef std::vector <sf::Sprite*> SpriteVector;
	SpriteVector mSpriteVector;

	float mConstVelocity;

};

#endif