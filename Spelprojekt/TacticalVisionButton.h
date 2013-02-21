#ifndef TACTICALVISIONBUTTON
#define TACTICALVISIONBUTTON
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\Vector2.hpp>
#include "Gui.h"
#include "AbilityButton.h"

class TacticalVisionButton : public AbilityButton {

public:

	TacticalVisionButton(sf::Vector2f position, std::string texture,float cooldown, Gui* gui);
	~TacticalVisionButton();
	virtual void update();
	virtual sf::Sprite* getSprite();
	virtual void setClicked(bool boolean);
	void activateTac();

private:

	sf::Texture* mTexture;
	sf::Sprite mSprite;
	bool mClicked;
	Gui* mGui;
	int mFrames;
	sf::Clock mClickCooldownTimer, mCooldownTimer;
	float mClickCooldown, mCooldown;


};


#endif