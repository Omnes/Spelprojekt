#include "Scene.h"
#include "WindowManager.h"
#include "SoundManager.h"


Scene::Scene(SpritesWithBoolPairs sprites,std::string voice, std::vector<std::pair<sf::Text,float>> texts, float duration)
	: mSprites(sprites)
	, mVoice(voice)
	, mTexts(texts)
	, mCompleted(false)
	, mDuration(duration)
	, mIsStarted(false){
		mAlpha = 0;


}

Scene::~Scene(){
	while(!mSprites.empty()){
		delete mSprites.back().first;
		mSprites.pop_back();
	}

}


void Scene::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	for(SpritesWithBoolPairs::iterator i = mSprites.begin(); i != mSprites.end();i++){
		window->draw(*(*i).first);
	}
	
	if(mIsStarted){
		float curMin = 0;
		float curMax = 0;
		float goalTime = mTimer.getElapsedTime().asSeconds();

		for(int i = 0; i < mTexts.size();i++){
			curMin = curMax;
			curMax += mTexts[i].second;
			if(curMin <= goalTime && curMax > goalTime){
				window->draw(mTexts[i].first);
				//break;
			}
		}
	}
}

void Scene::play(){
	SoundManager::getInst().playVoice(mVoice);
	mIsStarted = true;
	mTimer.restart();

}

bool Scene::isCompleted(){
	//byt kanske ut mot soundmanager.getsoundplayed eller liknanade
	return mIsStarted && mTimer.getElapsedTime().asSeconds() > mDuration;
}

bool Scene::fadeIn(){
	if(mAlpha < 1){
		mAlpha += 1.f/30;
		for(SpritesWithBoolPairs::iterator i = mSprites.begin(); i != mSprites.end(); i++){
			if((*i).second.first){
				(*i).first->setColor(sf::Color(255,255,255,255*mAlpha));
			}
		}
		return true;
	}
	return false;
}

bool Scene::fadeOut(){
	if(mAlpha > 0){
		mAlpha -= 1.f/30;
		for(SpritesWithBoolPairs::iterator i = mSprites.begin(); i != mSprites.end(); i++){
			if((*i).second.second){
				(*i).first->setColor(sf::Color(255,255,255,255*mAlpha));
			}
		}
		return true;
	}
	return false;
}

bool Scene::isStarted(){
	return mIsStarted;
}

