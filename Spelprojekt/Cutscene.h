#ifndef CUTSCENE
#define CUTSCENE
#include "States.h"
#include <vector>
#include <SFML\Graphics\Sprite.hpp>

class Scene;

class Cutscene : public States{
public:
	Cutscene(std::string filepath);
	~Cutscene();

	void update();
	void render();

	void loadFromFile(std::string file);
	void goToNext();

	std::string getMusic();

private:
	typedef std::vector<Scene*> SceneVector;
	typedef std::pair<SceneVector,sf::Sprite*> Enviroment;
	typedef std::pair<bool,bool> BoolPair;

	typedef std::vector<Enviroment> Enviroments;
	Enviroments mEnviroments;

	int mCurrentEnviroment;
	int mCurrentScene;

	std::string mMusic;

};




#endif