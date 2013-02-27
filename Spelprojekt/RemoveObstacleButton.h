#ifndef REMOVEOBSTACLEBUTTON
#define REMOVEOBSTACLEBUTTON

#include "AbilityButton.h"
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>

#include "ParticleSystem.h"
#include "Emitter.h"

class Gui;

class RemoveObstacleButton: public AbilityButton{
public:
	RemoveObstacleButton(std::vector<std::string> obstacle,sf::Vector2f position, std::string texture,float cooldown,std::string particleName,int EmittAmount, Gui* gui);

	virtual void update();
	virtual sf::Sprite* getSprite();
	virtual void setClicked(bool boolean);
	void killRelativePositionEntity(sf::Vector2f mousePosition);
	bool findID(std::string);
	
	~RemoveObstacleButton();

private:
	std::vector<std::string> mObstacles;
	bool mClicked;
	sf::Texture* mTexture;
	sf::Sprite mSprite;
	int mFrames;
	float mCooldown;
	float mClickCooldown;
	sf::Clock mClickCooldownTimer;
	sf::Clock mCooldownTimer;
	Gui* mGui;

	int mEmittAmount;
	ParticleSystem mParticleSystem;
	Emitter mEmitter;

	ParticleSystem mSparksOnObstacles;
	ParticleSystem mSparksOnButton;



};



#endif