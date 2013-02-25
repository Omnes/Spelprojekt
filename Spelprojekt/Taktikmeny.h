#ifndef TAKTIKMENY
#define TAKTIKMENY

#include "States.h"
#include "AnimalPrototype.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "FakeAbilityButton.h"

class TacticMenuButton;
class LevelManager;
class Spot;

class TaktikMeny: public States{
public:
	virtual void update();
	virtual void render();
	void receiveAnimals();
	void placeSpots();

	void createAnimals(); 

	void isClicked();
	void isNotClicked();

	void readFromFile();

	std::string getMusic();

	bool getFreeSpots();

	void setSpeed(); // växt vs kött

	~TaktikMeny();
	TaktikMeny();

private:

	AnimalPrototype* mCurrentDragAnimal;

	typedef std::vector<AnimalPrototype*> FakeAnimals;
	FakeAnimals mFakeAnimals;

	typedef std::vector <Entity*> AnimalVector;
	AnimalVector mAnimalVector;

	typedef std::vector <Spot*> SpotVector;
	SpotVector mSpotVector;

	typedef std::vector <int> LevelVector;  // kanske kan göras lokalt
	LevelVector mLevelVector;

	typedef std::vector <AnimalPrototype*> AnimalOnLevelsVector;  // kanske kan göras lokalt
	AnimalOnLevelsVector mAnimalOnLevelsVector;

	typedef std::vector <int> PosVector;
	PosVector mPosVector;

	typedef std::vector <float> SpeedVector;
	SpeedVector mSpeedVector;

	typedef std::vector <sf::Sprite> BgVector;
	BgVector mBgVector;

	int mLevelTop, mLevelMiddle, mLevelGround;

	bool mDown;

	sf::Vector2f mGrabOffset;

	std::string mMusic;

	TacticMenuButton* mButton;

	FakeAbilityButton* mAbilityButton;

	bool mAllSpotsTaken;

	sf::Sprite mAnimalSpriteBg;

	sf::Sprite mGui;

};


#endif