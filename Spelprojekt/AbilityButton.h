#ifndef ABILITYBUTTON
#define ABILITYBUTTON
#include <SFML\Graphics\Sprite.hpp>

class AbilityButton{
public:
	virtual void update()=0;
	virtual sf::Sprite* getSprite()=0;
	virtual void setClicked(bool boolean)=0;
	virtual ~AbilityButton(){};
	AbilityButton(){};
	

private:



};



#endif