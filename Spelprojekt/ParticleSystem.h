#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <queue>
#include <vector>
#include <SFML\Graphics\BlendMode.hpp>

namespace sf{
	class RenderWindow;
}

class ParticlePrototype;
struct Particle;

class CompareParticleLife{
public:
	bool operator()(Particle* p1, Particle* p2);
};

class ParticleSystem{
public:

	Particle* getRenewedParticle();
	void update();
	void render(sf::RenderWindow& window);
	ParticlePrototype* getPrototype();
	void setPrototype(ParticlePrototype* prototype);
	void setBlendMode(sf::BlendMode blendMode);
	int getActiveParticles();

	ParticleSystem(ParticlePrototype* prototype, int amount);
	ParticleSystem(std::string name, int amount);
	~ParticleSystem();
private:

	void createParticles(int amount);
	void destroyParticles();
	typedef std::priority_queue<Particle*, std::vector<Particle*>, CompareParticleLife> ParticleQueue;
	ParticleQueue mParticleQueue;
	typedef std::vector<Particle*> ParticleVector;
	ParticleVector mParticleVector;
	ParticlePrototype* mPrototype;
	int mActiveParticles;
	sf::BlendMode mBlendMode;
};

#endif


