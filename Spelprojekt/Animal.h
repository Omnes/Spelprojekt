#ifndef ANIMAL
#define ANIMAL

#include <vector>
#include <set>
#include <SFML\Graphics\Sprite.hpp>

class Animation;

class Animal{

public:
	Animal(Animation* animation, sf::Vector2f position, float speed);
	~Animal();
	void update();
	sf::Sprite* getSprite();

private:
	Animation* mAnimation;
	int currentAnimation;
	float mSpeed;
	sf::Vector2f mPosition;
	//std::set<SpeedMod*> modVector;

};





#endif