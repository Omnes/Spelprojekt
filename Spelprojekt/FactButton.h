#ifndef FACTBUTTON	
#define FACTBUTTON
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Audio\Sound.hpp>
#include "GlobalButtonTimer.h"
#include "ParticleSystem.h"
#include "Emitter.h"
#include "tinyxml2.h"


class FactButton{

public:

	FactButton(sf::Vector2f pos, std::string evt, std::string img, std::string sound);
	~FactButton();
	void update();
	sf::Sprite& getSprite();
	bool readFile();

private:
	
	ParticleSystem mSmokeSystem;
	Emitter mEmitter;

	sf::Vector2f mPosition;
	std::string mEvent;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture mTexture;

	int mTimer;

	bool mNewFact;

	int mCurrentImage;
};

#endif