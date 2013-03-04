#include "Scene.h"
#include "WindowManager.h"
#include "SoundManager.h"


Scene::Scene(sf::Sprite* sprite,std::string voice, sf::Text text)
	: mSprite(sprite)
	, mVoice(voice)
	, mText(text)
	, mCompleted(false){


}

Scene::~Scene(){
	delete mSprite;

}


void Scene::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	
	window->draw(*mSprite);
	window->draw(mText);
}

void Scene::play(){
	//spela upp voiceovern

}

bool Scene::isCompleted(){
	//byt kanske ut mot soundmanager.getsoundplayed eller liknanade
	return mCompleted;
}