#ifndef LEVELFINISHED
#define LEVELFINISHED
#include "States.h"
#include <SFML\Graphics\Sprite.hpp>
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

private:

	Button mButton;
	std::vector<sf::Sprite*> mAliveVector, mDeadVector;
};

#endif