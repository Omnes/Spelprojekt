#ifndef LEVELFINISHED
#define LEVELFINISHED
#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <vector>
#include "Button.h"


class LevelFinished : public States{

public:
	LevelFinished();
	~LevelFinished();
	virtual void update();
	virtual void render();
	std::vector<sf::Sprite*> loadAnimals(std::vector<std::string> animalvector);
	void setPosition();

	std::string getMusic();

private:
	sf::Sound mStampSound;
	Button mButton;
	std::vector<sf::Sprite*> mAliveVector, mDeadVector, mStampVector;
	std::string mMusic;
	sf::Clock mStampDelay;
	int mStampIndex;

	sf::Sprite mBackground;
};

#endif