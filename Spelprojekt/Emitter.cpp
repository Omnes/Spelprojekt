#include "Emitter.h"
#include "Particle.h"
#include "ParticleSystem.h"



Emitter::Emitter(const sf::Vector2f& position){
	mPosition = position;
}

void Emitter::burst(ParticleSystem& ps,int amount){

	for(int i = 0; i < amount;++i){
		Particle* p = ps.getRenewedParticle();
		p->mPosition = mPosition;
	}
}

void Emitter::burst(ParticleSystem& ps,sf::FloatRect& rect,int amount){

	for(int i = 0; i < amount;++i){
		Particle* p = ps.getRenewedParticle();

		sf::Vector2f pos;
		pos.x = mPosition.x+rect.left + (rand()%(int)rect.width);
		pos.y = mPosition.y+rect.top + (rand()%(int)rect.height);

		p->mPosition = pos;
	}
}

void Emitter::burst(ParticleSystem& ps,float radius,int amount){

	for(int i = 0; i < amount;++i){
		Particle* p = ps.getRenewedParticle();

		float dir = (float) rand() / ((float) RAND_MAX / 360);
		float length = (float) rand() / ((float) RAND_MAX / radius);
		sf::Vector2f pos = mPosition + sf::Vector2f(std::cos(dir * 3.14f / 180), -std::sin(dir * 3.14f / 180))*length;

		p->mPosition = pos;
	}
}

Emitter::~Emitter(){
}
