#ifndef PAGEBUTTON
#define PAGEBUTTON
#include <string>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>

#include <SFML\System\Clock.hpp>


class Animalipedia;

class PageButton{

public:

	PageButton(sf::Vector2f pos,int flipNumber,std::string img, std::string sound, Animalipedia* wiki);
	~PageButton();
	void update();
	sf::Sprite& getSprite();

private:

	sf::Vector2f mPosition;

	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture *mTexture;
	sf::Sound mSound;
	sf::SoundBuffer *mSoundBuffer;
	int mCurrentImage;
	int mFlipNumber;
	Animalipedia* mWiki;

	sf::Clock mClickCooldown;

};


#endif