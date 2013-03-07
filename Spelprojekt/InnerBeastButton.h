#ifndef INNERBEASTBUTTON
#define INNERBEASTBUTTON
#include "AbilityButton.h"
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>
#include <vector>
#include "InnerBeastArrow.h"
#include "Animal.h"
#include "Animation.h"
#include <SFML\Audio\Sound.hpp>

class Gui;

class InnerBeastButton: public AbilityButton{
public:
	InnerBeastButton(sf::Vector2f position, std::string texture,float cooldown,float speedincrease,float duration, std::string soundFX,Gui* gui);

	virtual void update();
	virtual sf::Sprite* getSprite();
	virtual void setClicked(bool boolean);
	
	~InnerBeastButton();

private:
	float mLevel;
	bool mClicked;
	sf::Texture* mTexture;
	sf::Sprite mSprite;
	int mFrames;
	float mCooldown;
	float mClickCooldown;
	float mSpeedIncrease;
	float mSpeedDuration;
	sf::Clock mClickCooldownTimer;
	sf::Clock mCooldownTimer;
	sf::Clock mSpeedTimer;
	Gui* mGui;
	//std::vector<InnerBeastArrow> mArrows; 
	std::vector<Animation*> mAnimations;
	std::vector<Animal*> mAnimals;
	Animation* mAnimation;

	sf::Sound mSoundFX;

};



#endif