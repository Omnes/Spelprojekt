#include "ParticleSystem.h"
#include "Particle.h"
#include "ParticlePrototype.h"
#include <SFML\System\Thread.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <functional>
#include "ParticleManager.h"



ParticleSystem::ParticleSystem(ParticlePrototype* prototype, int amount)
	: mPrototype(prototype)
	, mBlendMode(sf::BlendAlpha){

		ParticleManager::getInst().addSystem(this);
		mParticleVector.reserve(amount);
		createParticles(amount);
}

ParticleSystem::ParticleSystem(std::string name, int amount)
	: mPrototype(&ParticleManager::getInst().getPrototype(name))
	, mBlendMode(sf::BlendAlpha){

		ParticleManager::getInst().addSystem(this);
		mParticleVector.reserve(amount);
		createParticles(amount);
}

void ParticleSystem::createParticles(int amount){
	for (int i = 0 ; i < amount ; i ++){
		Particle* particle = new Particle;
		mParticleQueue.push(particle);
		mParticleVector.push_back(particle);
	}
}

void ParticleSystem::setBlendMode(sf::BlendMode blendMode){
	mBlendMode = blendMode;
}

void ParticleSystem::setPrototype(ParticlePrototype* prototype){
	delete mPrototype;
	mPrototype = prototype;
}

ParticlePrototype* ParticleSystem::getPrototype(){
	return mPrototype;
}

int ParticleSystem::getActiveParticles(){
	return mActiveParticles;
}


Particle* ParticleSystem::getRenewedParticle(){
	Particle* particle = mParticleQueue.top();
	mParticleQueue.pop();
	mPrototype->setValuesOn(*particle);
	mParticleQueue.push(particle);
	return particle;
}

void ParticleSystem::update(){
	
	mActiveParticles = 0;
	for(ParticleVector::iterator i = mParticleVector.begin(); i != mParticleVector.end(); ++i){
		
		if((*i)->mLife > 0){
			mActiveParticles ++;
			(*i)->update();
		}
	}
}

void ParticleSystem::render(sf::RenderWindow& window){

	for(ParticleVector::iterator i = mParticleVector.begin(); i != mParticleVector.end(); ++i){
		if((*i)->mLife > 0){
			window.draw((*i)->getSprite(),mBlendMode);
		}
	}
}


void ParticleSystem::destroyParticles(){

	for(ParticleVector::iterator i = mParticleVector.begin(); i != mParticleVector.end(); ++i){
		delete *i;
	}
	mParticleVector.clear();
}


ParticleSystem::~ParticleSystem(){

	destroyParticles();
	ParticleManager::getInst().removeSystem(this);

}

bool CompareParticleLife::operator()(Particle* p1,Particle* p2){
	return p1->mLife > p2->mLife;
}