#ifndef STARTMENY
#define STARTMENY

class StartMeny: public States{
public:
	virtual void update();
	virtual void render();'
	StartMeny();
	~StartMeny();

private:
	std::vector<Button*> mButtons;
	
};


#endif