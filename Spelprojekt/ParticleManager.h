#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H


#include <vector>
#include <map>
#include <string>

namespace sf{
	class RenderWindow;
}
class ParticleSystem;
class ParticlePrototype;

class ParticleManager{

public:
	void addSystem(ParticleSystem* ps);
	void removeSystem(ParticleSystem* ps);
	void update();
	void render(sf::RenderWindow& window);
	void savePrototype(ParticlePrototype &prototype,std::string name);
	ParticlePrototype& getPrototype(std::string name);
	int getActiveParticleCount();
	static ParticleManager& getInst();
	void loadPrototype(std::string filepath);
	void loadAllParticlesFromFile(std::string filePath);

private:
	ParticleManager();
	~ParticleManager();
	ParticleManager& operator=(ParticleManager&);
	ParticleManager(const ParticleManager&);

	typedef std::vector<ParticleSystem*> Systems;
	Systems mSystems;
	typedef std::map<std::string,ParticlePrototype> PrototypeMap;
	PrototypeMap mPrototypeMap;
};

#endif

