#ifndef TAKTIKMENY
#define TAKTIKMENY

#include "States.h"
#include "AnimalPrototype.h"

class LevelManager;
class Spot;

class TaktikMeny: public States{
public:
	virtual void update();
	virtual void render();
	void receiveAnimals();
	void placeSpots();
	~TaktikMeny();
	TaktikMeny();

private:

	AnimalPrototype* mCurrentDragAnimal;
	typedef std::vector<AnimalPrototype*> FakeAnimals;
	FakeAnimals mFakeAnimals;

	typedef std::vector <Spot*> SpotVector;
	SpotVector mSpotVector;

	typedef std::vector <float> LevelVector;
	LevelVector mLevelVector;

	bool mDown;

};


#endif