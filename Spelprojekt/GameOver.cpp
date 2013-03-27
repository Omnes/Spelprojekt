#include "GameOver.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "FontMaster.h"

int GameOver::sRetryCount = 0;

GameOver::GameOver()
	: mReturnToMain(sf::Vector2f(430,520),"popStateTwice","Resources/Menu/GameOverMenu/MenuButton.png","Resources/Sound/Menu/Menu_click.wav")
	, mBackground(*ResourceManager::getInst().getTexture("Resources/Menu/GameOverMenu/GameOver.png"))
	, mRetryLevel(sf::Vector2f(570,360), "retry", "Resources/Menu/GameOverMenu/RetryButton.png", "Resources/Sound/Menu/Menu_click.wav"){

		std::string string;
		string.push_back((char)'0' + (2-sRetryCount));
		string += " försök kvar!";
		if(sRetryCount == 2){
			string = "";
		}
		mRetryText.setString(string);
		mRetryText.setPosition(sf::Vector2f(520,460));
		mRetryText.setFont(FontMaster::sFont);
		mMusic = "Resources/Sound/Music/Title_Screen_";

		
}



void GameOver::update(){
	mReturnToMain.update();
	if(sRetryCount < 2){ 
		mRetryLevel.update();
	}

}

void GameOver::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();
	window->draw(mBackground);
	window->draw(mReturnToMain.getSprite());
	if(sRetryCount < 2){
		window->draw(mRetryLevel.getSprite());
	}
	window->draw(mRetryText);
}

GameOver::~GameOver(){

}

std::string GameOver::getMusic(){
	return mMusic;
}