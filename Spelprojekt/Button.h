#ifndef BUTTON
#define BUTTON
#include <string>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>

class Button{

public:

	Button(sf::Vector2f pos, std::string evt, std::string img);
	~Button();
	void update();
	sf::Sprite& getSprite();

private:

	sf::Vector2f mPosition;
	std::string mEvent;
	std::string mImage;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture mTexture;
	int mCurrentImage;

};


#endif