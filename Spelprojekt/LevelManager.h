#ifndef LEVELMANAGER
#define LEVELMANAGER
#include <vector>
#include <string>


class Layer;
class AnimalPrototype;
class Entity;
class ActiveLayer;
class Camera;

class LevelManager{
public:
	void setFilePath(std::string filePath);
	std::string getFilePath();
	std::vector<AnimalPrototype*> getAnimalsOnLevel();
	void setAliveAnimals(std::vector<std::string>& aliveVector);
	void setDeadAnimals(std::vector<std::string>& deadVector);
	void setAnimalPosition(std::vector<Entity*>);
	std::vector<std::string> getAliveAnimals();
	std::vector<std::string> getDeadAnimals();
	std::vector<std::string>* getDeadAnimalCollection();
	std::vector<Layer*> loadLayers();
	static LevelManager& getInst();
	ActiveLayer* getActiveLayer();
	void setCamera(Camera* camera);
	Camera* getCamera();
	int getLevelLength();

private:
	//std::vector<Layer*> layers;
	std::string mFilePath;
	std::vector<Entity*> placedAnimals;
	std::vector<std::string> mAliveAnimals, mDeadAnimals, mDeadAnimalCollection;
	ActiveLayer* mActiveLayer;
	Camera* mThisCamera;
	int mLevellength;

	LevelManager& operator=(const LevelManager&);
	LevelManager(const LevelManager&);
	LevelManager();
	~LevelManager();
};





#endif