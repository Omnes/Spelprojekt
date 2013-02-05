#ifndef GUI
#define GUI

#include <vector>

class AbilityButton;

class Gui{
public:
	void update();
	void render();

private:
	std:vector<AbilityButton*> mButtons;

};


#endif