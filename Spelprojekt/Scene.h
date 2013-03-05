#ifndef SCENE
#define SCENE

#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Clock.hpp>

class Scene{
public:

	Scene(std::vector<std::pair<sf::Sprite*,std::pair<bool,bool>>> sprites,std::string voice, sf::Text text, float duration);
	~Scene();

	void render();
	void play();
	bool isStarted();
	bool isCompleted();

	bool fadeIn();
	bool fadeOut();

private:
	bool mCompleted;
	float mDuration;
	sf::Clock mTimer;
	bool mIsStarted;
	float mAlpha;
	sf::Text mText;
	std::string mVoice;
	typedef std::vector<std::pair<sf::Sprite*,std::pair<bool,bool>>> SpritesWithBoolPairs;
	SpritesWithBoolPairs mSprites;

};

#endif