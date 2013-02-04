#ifndef REMOVEOBSTACLEBUTTON
#define REMOVEOBSTACLEBUTTON

#include "AbilityButton.h"
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>

class RemoveObstacleButton: public AbilityButton{
public:
	RemoveObstacleButton(std::string obstacle,sf::Vector2f position, std::string texture);

	virtual void update();
	virtual sf::Sprite* getSprite();
	virtual void setClicked(bool boolean);
	
	~RemoveObstacleButton();

private:
	std::string mObstacle;
	bool mClicked;
	sf::Texture* mTexture;
	sf::Sprite mSprite;


};



#endif