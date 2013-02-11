#ifndef EMITTER_H
#define EMITTER_H

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>


class ParticleSystem;

class Emitter{
public:

	Emitter(const sf::Vector2f& position);
	Emitter(){};
	~Emitter();
	void burst(ParticleSystem& ps, int amount);
	void burst(ParticleSystem& ps,sf::FloatRect& rect,int amount);
	void burst(ParticleSystem& ps,float radius,int amount);
	void setPosition(const sf::Vector2f& position){mPosition = position;}

private:

	sf::Vector2f mPosition;
};

#endif

