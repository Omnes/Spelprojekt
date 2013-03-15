#ifndef ANIMALIPEDIABUTTON
#define ANIMALIPEDIABUTTON
#include <string>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include <SFML\Graphics\Text.hpp>
#include "Emitter.h"
#include "ParticleSystem.h"

class Animalipedia;


class AnimalipediaButton{

public:

	AnimalipediaButton(sf::Vector2f pos, std::string page, std::string title, std::string sound, Animalipedia* wiki);
	~AnimalipediaButton();
	void update();
	void render();
	void setLocked(int level);
	void setNewInfo(bool boolean);
	void setPosition(sf::Vector2f pos);

private:

	std::string mInfo;
	sf::Text mTitle;

	Animalipedia* mWiki;

	int mLocked;
	bool mNewInfo;
	Emitter mEmitter;
	ParticleSystem mNewEffekt;

	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	sf::IntRect mRectangle;
	sf::Texture *mTexture;
	sf::Sound mSound;
	sf::SoundBuffer *mSoundBuffer;
	int mCurrentImage;

};


#endif