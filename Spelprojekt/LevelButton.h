#ifndef LEVELBUTTON	
#define LEVELBUTTON
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>

class LevelButton{

public:

	LevelButton(sf::Vector2f pos, std::string evt, std::string img, std::string level);
	~LevelButton();
	void update();
	sf::Sprite& getSprite();

private:
	
	sf::Vector2f mPosition;
	std::string mEvent;
	std::string mImage;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture mTexture;
	std::string mLevel;
	int mCurrentImage;
};

#endif