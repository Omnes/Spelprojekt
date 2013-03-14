#ifndef OPTIONSLIDER
#define OPTIONSLIDER

#include <SFML\System\Vector2.hpp>
#include <string>
#include "ResourceManager.h"
#include "tinyxml2.h"
#include "WindowManager.h"
#include <SFML\Window\Mouse.hpp>
#include "SoundManager.h"


class OptionSlider{
public:
	OptionSlider(sf::Vector2f posBg, std::string element,std::string attribute);
	~OptionSlider();
	void render();
	void update();
	void saveSettings();
	void clamPos();




private:

	sf::Texture* mTex;
	sf::Sprite mSprite, mSpriteBg;
	bool mPressed;
	float mMaxPos, mMinPos, mPosRatio, mVolRatio;
	int mVolume;

	std::string mElement;
	std::string mAttribute;

};

#endif