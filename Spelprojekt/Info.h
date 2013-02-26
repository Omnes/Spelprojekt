#ifndef INFO
#define INFO

#include <vector>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Text.hpp>

class Info{
public:
	Info(std::string elementName);
	~Info();
	void setUnlockedInfo(bool boolean);

	void render();

private:

	bool mExtraInfoUnlocked;

	sf::Sprite mPicture;
	sf::Text mStandardText;
	sf::Text mLockedText;
	sf::Sprite mPadlock;

};


#endif