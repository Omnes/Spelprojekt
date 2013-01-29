#ifndef TAKTIKMENY
#define TAKTIKMENY

#include "States.h"
#include "AnimalPrototype.h"

class TaktikMeny: States{
public:
	virtual void update();
	virtual void render();
	~TaktikMeny();
	TaktikMeny();

private:

	AnimalPrototype* mCurrentDragAnimal;
	typedef std::vector<AnimalPrototype*> FakeAnimals;
	FakeAnimals mFakeAnimals;

	bool mDown;

};


#endif