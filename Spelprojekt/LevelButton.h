#ifndef LEVELBUTTON	
#define LEVELBUTTON
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>

#include <string>

class LevelButton{

public:

	LevelButton(sf::Vector2f pos, std::string evt, std::string img, std::string level);
	~LevelButton();
	void update();
	sf::Sprite& getSprite();
	std::string getLevel();

	bool getAlive(); //tror denna behövs <----
	void setAlive(bool alive);

	bool getActive();
	void setActive(bool active);

private:
	
	sf::Vector2f mPosition;
	std::string mEvent;
	std::string mImage;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture mTexture;
	std::string mLevel;

	bool mAlive, mActive;

	int mCurrentImage;
};

#endif