#ifndef BUTTON
#define BUTTON
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
#include "Emitter.h"
#include "ParticleSystem.h"



class Button{

public:

	Button(sf::Vector2f pos, std::string evt, std::string img, std::string sound);
	~Button();
	void update();
	sf::Sprite& getSprite();

private:

	sf::Vector2f mPosition;
	std::string mEvent;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture *mTexture;
	sf::Sound mSound;
	sf::SoundBuffer *mSoundBuffer;
	int mCurrentImage;
	sf::Clock mTimer;
	float mButtonTime;
	bool mPressed;



};


#endif