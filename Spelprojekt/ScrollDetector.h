#ifndef SCROLLDETECTOR
#define SCROLLDETECTOR



class ScrollDetector{
public:
	static void setScrollDelta(float delta){
		//if(delta != 0)
			scrollDelta = delta;
	}
	static float getScrollDelta(){
		return scrollDelta;
	}
private:
	static float scrollDelta;
};

#endif