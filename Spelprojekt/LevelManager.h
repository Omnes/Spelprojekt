#ifndef LEVELMANAGER
#define LEVELMANAGER
#include <vector>
#include <string>

class Layer;
//class LevelManagerImp;
class Place_Animal;
class Entity;

class LevelManager{
public:
	void setFilePath(std::string filePath);
	/*std::vector<Place_Animal*> getAnimalsOnLevel();*/
	void setAnimalPosition(std::vector<Entity*>);
	std::vector<Layer*> loadLayers();
	static LevelManager& getInst();

private:
	//std::vector<Layer*> layers;
	std::string mFilePath;
	std::vector<Entity*> placedAnimals;

	LevelManager& operator=(const LevelManager&);
	LevelManager(const LevelManager&);
	LevelManager();
	~LevelManager();
};





#endif