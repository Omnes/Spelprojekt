#ifndef TAKTIKMENY
#define TAKTIKMENY

#include "States.h"
#include "AnimalPrototype.h"
#include "Entity.h"

class LevelManager;
class Spot;

class TaktikMeny: public States{
public:
	virtual void update();
	virtual void render();
	States* createNew();
	void receiveAnimals();
	void placeSpots();

	void createAnimals(); 

	void isClicked();
	void isNotClicked();

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

	typedef std::vector <int> LevelVector;
	LevelVector mLevelVector;

	typedef std::vector <int> PosVector;
	PosVector mPosVector;

	typedef std::vector <float> SpeedVector;
	SpeedVector mSpeedVector;

	int mLevelTop, mLevelMiddle, mLevelGround;

	bool mDown;

	sf::Vector2f mGrabOffset;

};


#endif