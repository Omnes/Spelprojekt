#ifndef LEVELMANAGER
#define LEVELMANAGER
#include <vector>
#include <string>
#include "tinyxml2.h"


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
	void preloadBackgrounds();
	std::vector<std::string> getAliveAnimals();
	std::vector<std::string> getDeadAnimals();
	void setDeadAnimalCollection(std::vector <std::string> deadAnimals);

	std::vector<std::string>* getDeadAnimalCollection();

	std::vector<Layer*> loadLayers();
	std::string getMusicOnLevel();
	std::vector<std::string> getAbilitiesOnLevel();
	std::string getGuiTextureFilepath();
	static LevelManager& getInst();
	ActiveLayer* getActiveLayer();
	void setCamera(Camera* camera);
	Camera* getCamera();
	int getLevelLength();
	std::vector <float> getLevelsOnLevel(); //niv�er p� en bana 

	void addAliveAnimals(std::vector <std::string> fakeAnimals);

private:
	//std::vector<Layer*> layers;
	std::string mFilePath;
	tinyxml2::XMLDocument* mDoc;

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