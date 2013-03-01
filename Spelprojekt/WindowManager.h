#ifndef WINDOWMANAGER
#define WINDOWMANAGER
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>

class WindowManager{
public:

	static WindowManager& getInst();
	sf::RenderWindow* getWindow();
	sf::View* getDefaultView();
	void createWindow();
	sf::Sprite* getCursor();

private:

	sf::RenderWindow* mWindow;
	sf::View* mDefaultView;
	WindowManager();
	WindowManager& operator=(const WindowManager);
	WindowManager(const WindowManager&);
	~WindowManager();
	sf::Sprite mAim;
};


#endif