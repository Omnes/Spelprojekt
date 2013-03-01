#ifndef WINDOWMANAGER
#define WINDOWMANAGER
#include <SFML\Graphics\RenderWindow.hpp>

class WindowManager{
public:

	static WindowManager& getInst();
	sf::RenderWindow* getWindow();
	sf::View* getDefaultView();
	void createWindow();

private:

	sf::RenderWindow* mWindow;
	sf::View* mDefaultView;
	WindowManager();
	WindowManager& operator=(const WindowManager);
	WindowManager(const WindowManager&);
	~WindowManager();
};


#endif