#ifndef REMOVEOBSTACLEBUTTON
#define REMOVEOBSTACLEBUTTON

#include "AbilityButton.h"
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>

class Gui;

class RemoveObstacleButton: public AbilityButton{
public:
	RemoveObstacleButton(std::string obstacle,sf::Vector2f position, std::string texture, Gui* gui);

	virtual void update();
	virtual sf::Sprite* getSprite();
	virtual void setClicked(bool boolean);
	void killRelativePositionEntity(sf::Vector2f mousePosition);
	
	~RemoveObstacleButton();

private:
	std::string mObstacle;
	bool mClicked;
	sf::Texture* mTexture;
	sf::Sprite mSprite;
	int mFrames;
	float mCooldown;
	float mClickCooldown;
	sf::Clock mClickCooldownTimer;
	sf::Clock mCooldownTimer;
	Gui* mGui;



};



#endif