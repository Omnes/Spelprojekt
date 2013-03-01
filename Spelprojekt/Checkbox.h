#ifndef CHECKBOX
#define CHECKBOX

#include <SFML\System\Clock.hpp>
#include <string>
#include <SFML\Graphics\Sprite.hpp>

class Checkbox{
public:
	Checkbox(sf::Vector2f position,std::string element,std::string attribute);
	~Checkbox();
	void update();
	void render();
	void saveSetting();

private:
	bool mChecked;
	int mFrames;
	int mCurrentImage;
	std::string mElement;
	std::string mAttribute;
	float mClickCooldown;
	sf::Clock mClickCooldownTimer;
	sf::Texture* mTex;
	sf::Sprite mSprite;

};


#endif