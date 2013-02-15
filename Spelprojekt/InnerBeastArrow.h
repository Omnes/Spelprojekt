#ifndef INNERBEASTARROW
#define INNERBEASTARROW
#include <string>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>

class InnerBeastArrow{

public:

	InnerBeastArrow(sf::Vector2f pos, std::string img);
	~InnerBeastArrow();
	void update();
	sf::Sprite& getSprite();


private:

	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture *mTexture;
	int mCurrentImage;

};


#endif