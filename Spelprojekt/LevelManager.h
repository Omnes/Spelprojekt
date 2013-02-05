#ifndef LEVELMANAGER
#define LEVELMANAGER
#include <vector>
#include <string>

class Layer;
//class LevelManagerImp;
class AnimalPrototype;
class Entity;
class ActiveLayer;
class Camera;

class LevelManager{
public:
	void setFilePath(std::string filePath);
	std::vector<AnimalPrototype*> getAnimalsOnLevel();
	void setAnimalPosition(std::vector<Entity*>);
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
	ActiveLayer* mActiveLayer;
	Camera* mThisCamera;
	int mLevellength;

	LevelManager& operator=(const LevelManager&);
	LevelManager(const LevelManager&);
	LevelManager();
	~LevelManager();
};





#endif