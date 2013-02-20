#ifndef TACTICMENUBUTTON
#define TACTICMENUBUTTON
#include <string>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include "Emitter.h"
#include "ParticleSystem.h"



class TaktikMeny;

class TacticMenuButton{

public:

	TacticMenuButton(sf::Vector2f pos, TaktikMeny* tacticMenu, std::string img, std::string sound);
	~TacticMenuButton();
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
	Emitter mEmitter;
	ParticleSystem mPartSystem;

	TaktikMeny* mTaktikMeny;

};


#endif