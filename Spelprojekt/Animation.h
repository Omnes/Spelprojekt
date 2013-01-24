#ifndef ANIMATION
#define ANIMATION
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Vector2.hpp>

class Animation{

public:

	Animation(sf::Texture *texture, int frametime, int frames);
	~Animation();
	void update();
	sf::Sprite* getSprite();
	void setCurrentAnimation(int animation);
	void setPosition(sf::Vector2f position);

private:

	sf::Texture* mTexture;
	sf::Clock mTimer;
	sf::IntRect mRectangle;
	sf::Sprite mSprite;
	int mFrametime, mFrames, mCurrentframe, mCurrentanimation;

};

#endif
