#include "GameOver.h"
#include "ResourceManager.h"
#include "WindowManager.h"

int GameOver::sRetryCount = 0;

GameOver::GameOver()
	: mReturnToMain(sf::Vector2f(500,500),"popStateTwice","Resources/Menu/GameOverMenu/MenuButton.png","Resources/Sound/test.wmv")
	, mLoadLast(sf::Vector2f(700,500),"popTwice","Resources/Misc/knapp2.jpg","Resources/Sound/test.wmv")
	, mBackground(*ResourceManager::getInst().getTexture("Resources/Menu/GameOverMenu/GameOver.png"))
	, mRetryLevel(sf::Vector2f(600,200), "retry", "Resources/Menu/GameOverMenu/RetryButton.png", "Resources/Sound/test.wmv"){

		mMusic = "Resources/Sound/Music/TitleScreen";
}



void GameOver::update(){
	mReturnToMain.update();
	//mLoadLast.update();
	if(sRetryCount < 2){ 
		mRetryLevel.update();
	}

}

void GameOver::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	window->draw(mBackground);
	window->draw(mReturnToMain.getSprite());
	//window->draw(mLoadLast.getSprite());
	if(sRetryCount < 2){
		window->draw(mRetryLevel.getSprite());
	}
}

GameOver::~GameOver(){

}

std::string GameOver::getMusic(){
	return mMusic;
}