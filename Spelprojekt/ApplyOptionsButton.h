#ifndef APPLYOPTIONSBUTTON
#define APPLYOPTIONSBUTTON

#include <string>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Audio\Sound.hpp>
#include <SFML\System\Clock.hpp>



class OptionsMeny;



class ApplyOptionsButton{

public:

	ApplyOptionsButton(sf::Vector2f pos,std::string img, std::string sound, OptionsMeny* options);
	~ApplyOptionsButton();
	void update();
	sf::Sprite& getSprite();

private:
	int mFrames;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	sf::Texture *mTex;
	sf::Sound mSound;
	int mCurrentImage;
	sf::Clock mClickCooldownTimer;
	float mClickCooldown;
	OptionsMeny* mOptionsMenu;

};


#endif