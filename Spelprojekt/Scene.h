#ifndef SCENE
#define SCENE

#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Sprite.hpp>

class Scene{
public:

	Scene(sf::Sprite* sprite,std::string voice, sf::Text text);
	~Scene();

	void render();
	void play();
	bool isCompleted();

private:
	bool mCompleted;
	sf::Text mText;
	std::string mVoice;
	sf::Sprite* mSprite;

};

#endif