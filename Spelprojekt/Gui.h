#ifndef GUI_H
#define GUI_H

#include <vector>
#include <SFML\Graphics\RenderWindow.hpp>

class AbilityButton;

class Gui{
public:
	void update();
	void render();
	void unclickAll();

	Gui();
	~Gui();

private:
	typedef std::vector<AbilityButton*> AbilityButtons;
	AbilityButtons mButtons;
	sf::RenderWindow* mWindow;

};


#endif