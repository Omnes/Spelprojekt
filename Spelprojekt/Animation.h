#ifndef ANIMATION
#define ANIMATION
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Vector2.hpp>

class Animation{

public:

	Animation(sf::Texture *texture, int frametime, int xframes, int yframes);
	~Animation();
	void update();
	sf::Sprite* getSprite();
	void setCurrentAnimation(int animation);
	void setPosition(sf::Vector2f position);
	void setFrameTime(float value);
	bool getHasPlayed();

private:

	bool mHasPlayed;

	sf::Texture* mTexture;
	sf::Clock mTimer;
	sf::IntRect mRectangle;
	sf::Sprite mSprite;
	int mFrametime, mFrames, mCurrentframe, mCurrentanimation, mOriginalFrameTime;

};

#endif
