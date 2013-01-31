#ifndef LEVELMANAGER
#define LEVELMANAGER
#include <vector>
#include <string>

class Layer;
//class LevelManagerImp;
class AnimalPrototype;
class Entity;

class LevelManager{
public:
	void setFilePath(std::string filePath);
	std::vector<AnimalPrototype*> getAnimalsOnLevel();
	void setAnimalPosition(std::vector<Entity*>);
	std::vector<Layer*> loadLayers();
	static LevelManager& getInst();
	Layer* getActiveLayer();

private:
	//std::vector<Layer*> layers;
	std::string mFilePath;
	std::vector<Entity*> placedAnimals;
	Layer* mActiveLayer;

	LevelManager& operator=(const LevelManager&);
	LevelManager(const LevelManager&);
	LevelManager();
	~LevelManager();
};





#endif