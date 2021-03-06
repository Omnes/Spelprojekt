#ifndef GUI_H
#define GUI_H

#include <vector>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>

class AbilityButton;

class Gui{
public:
	void update();
	void render();
	void unclickAll();
	void loadAbilites();

	Gui();
	~Gui();

private:
	typedef std::vector<AbilityButton*> AbilityButtons;
	AbilityButtons mButtons;
	sf::RenderWindow* mWindow;
	sf::Sprite mGuiSprite;
	std::vector<sf::Sprite*> mDeadAnimals;
	sf::Sprite mExtinct;

};


#endif