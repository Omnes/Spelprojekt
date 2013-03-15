#ifndef FACTBUTTON	
#define FACTBUTTON
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Audio\Sound.hpp>
#include "GlobalButtonTimer.h"



class FactButton{

public:

	FactButton(sf::Vector2f pos, std::string evt, std::string img, std::string sound);
	~FactButton();
	void update();
	sf::Sprite& getSprite();

private:
	
	sf::Vector2f mPosition;
	std::string mEvent;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture mTexture;

	int mCurrentImage;
};

#endif