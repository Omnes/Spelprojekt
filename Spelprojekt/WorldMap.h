#ifndef WORLDMAP
#define WORLDMAP
#include "States.h"
#include "LevelButton.h"

#include "SFML\Graphics\Texture.hpp"
#include "tinyxml2.h"
#include <string> // kanske inte behövs (se: saveToFile(std::string))

class WorldMap : public States{

public:

	WorldMap();
	~WorldMap();
	virtual void update();
	virtual void render();
	void readFromFile();
	void saveToFile(std::string levelName);

	std::string getMusic();

private:

	typedef std::vector <LevelButton*> ButtonVector;
	ButtonVector mButtonVector;

	typedef std::vector <std::string> PlayedLevels;
	PlayedLevels mPlayedLevels;

	std::string mMusic;

	sf::Texture mTexture;
	sf::Sprite mSprite;

	

};

#endif