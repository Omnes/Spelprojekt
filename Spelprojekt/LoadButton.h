#ifndef LOADBUTTON	
#define LOADBUTTON
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>

#include <string>

class LoadButton{

public:

	LoadButton(sf::Vector2f pos, std::string evt, std::string img, std::string sound);
	~LoadButton();
	void update();
	sf::Sprite& getSprite();

	void setActive();




private:
	
	sf::Vector2f mPosition;
	std::string mEvent;
	std::string mImage;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture mTexture;

	bool mActive;

	int mTimer, mTimerMax;

	int mCurrentImage;
};

#endif