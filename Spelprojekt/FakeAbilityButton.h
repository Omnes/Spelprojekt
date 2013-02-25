#ifndef FAKEABILITYBUTTON
#define FAKEABILITYBUTTON
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Vector2.hpp>
#include <string>

class FakeAbilityButton{

public:
	FakeAbilityButton(sf::Vector2f position, std::string buttontexture, std::string obstaclestexture);
	~FakeAbilityButton();
	void update();
	void render();

private:

	sf::Sprite* mSpriteButton;
	sf::Sprite* mSpriteInfo;
	sf::Vector2f mPosition;
	bool mButtonActivated;


};


#endif