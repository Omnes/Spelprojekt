#include "GameOver.h"
#include "ResourceManager.h"
#include "WindowManager.h"


GameOver::GameOver()
	:mReturnToMain(sf::Vector2f(500,500),"popTwice","Resources/Misc/knapp1.jpg","Resources/Sound/test.wmv")
	,mLoadLast(sf::Vector2f(700,500),"popTwice","Resources/Misc/knapp2.jpg","Resources/Sound/test.wmv")
	,mBackground(*ResourceManager::getInst().getTexture("Resources/Menu/GameOverScreenWithSadOcelotInTheMiddle.png")){

}



void GameOver::update(){
	mReturnToMain.update();
	mLoadLast.update();
}

void GameOver::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	window->draw(mBackground);
	window->draw(mReturnToMain.getSprite());
	window->draw(mLoadLast.getSprite());
}

GameOver::~GameOver(){

}