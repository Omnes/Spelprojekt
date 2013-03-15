#include "Cutscene.h"
#include "Scene.h"
#include "WindowManager.h"
#include <SFML\Window\Keyboard.hpp>
#include "tinyxml2.h"
#include "ResourceManager.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "FontMaster.h"


Cutscene::Cutscene(std::string file){
	loadFromFile(file);
	mCurrentEnviroment = 0;
	mCurrentScene = 0;

	WindowManager::getInst().getCursor()->setColor(sf::Color(0,0,0,0));
	SoundManager::getInst().setMusicVolume(5); // komihåg att ändra tillbaka detta efter betan!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! <----- LÄS DEN HÄR
	
}

Cutscene::~Cutscene(){
	WindowManager::getInst().getCursor()->setColor(sf::Color(255,255,255,255));

	while(!mEnviroments.empty()){
		while(!mEnviroments.back().first.empty()){
			delete mEnviroments.back().first.back();
			mEnviroments.back().first.pop_back();
		}
		delete mEnviroments.back().second;
		mEnviroments.pop_back();
	}

	SoundManager::getInst().loadSettings();
}

void Cutscene::goToNext(){
	
	if(mEnviroments[mCurrentEnviroment].first.size() > mCurrentScene+1){
		mCurrentScene ++;
	}else{
		mCurrentScene = 0;
		if(mEnviroments.size() > mCurrentEnviroment+1){
			mCurrentEnviroment ++;
		}else{
			StateManager::getInst().popState();
			return;
		}
	}
}

void Cutscene::update(){

	Scene* currentScene = mEnviroments[mCurrentEnviroment].first[mCurrentScene];
	if(!currentScene->isStarted()){
		if(!currentScene->fadeIn()){
			currentScene->play();
		}
	}

	if(currentScene->isCompleted()){
		if(!currentScene->fadeOut()){
			goToNext();
		}
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		StateManager::getInst().popState();
	}
}

void Cutscene::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->draw(*mEnviroments[mCurrentEnviroment].second);

	mEnviroments[mCurrentEnviroment].first[mCurrentScene]->render();
}

void Cutscene::loadFromFile(std::string file){
	tinyxml2::XMLDocument doc;
	doc.LoadFile(file.c_str());

	mMusic = doc.FirstChildElement("Cutscene")->Attribute("music");
	tinyxml2::XMLElement* env = doc.FirstChildElement("Cutscene")->FirstChildElement("Enviroment");
	while(env != 0){

		tinyxml2::XMLElement* sce = env->FirstChildElement("Scene");

		std::vector<Scene*> scenes;

		while(sce != 0){
			std::vector<std::pair<sf::Text,float>> texts;
			tinyxml2::XMLElement* elmText = sce->FirstChildElement("Text");

			while(elmText != 0){
				sf::Text text;
				text.setString(elmText->GetText());
				float tx = elmText->FloatAttribute("x");
				float ty = elmText->FloatAttribute("y");
				text.setPosition(tx,ty);
				text.setFont(FontMaster::sFont);
				float duration = elmText->FloatAttribute("duration");
				texts.push_back(std::pair<sf::Text,float>(text,duration));
				elmText = elmText->NextSiblingElement("Text");
			}

			std::string voice = sce->FirstChildElement("Voice")->Attribute("file");

			float duration = sce->FloatAttribute("duration");

			std::vector<std::pair<sf::Sprite*,std::pair<bool,bool>>> sprites;
			tinyxml2::XMLElement* img = sce->FirstChildElement("Image");

			while(img != 0){
				std::string texString = img->Attribute("texture");
				sf::Texture* tex = ResourceManager::getInst().getTexture(texString);
				sf::Sprite* sprite = new sf::Sprite(*tex);
				float sx = img->FloatAttribute("x");
				float sy = img->FloatAttribute("y");
				sprite->setPosition(sx,sy);
				bool fadeIn = img->BoolAttribute("fadeIn");
				bool fadeOut = img->BoolAttribute("fadeOut");

				if(fadeIn){
					sprite->setColor(sf::Color(255,255,255,0));
				}

				sprites.push_back(std::pair<sf::Sprite*,BoolPair>(sprite,BoolPair(fadeIn,fadeOut)));
				img = img->NextSiblingElement("Image");
			}

			Scene* scene = new Scene(sprites,voice,texts,duration);
			scenes.push_back(scene);
			sce = sce->NextSiblingElement();
		}
		

		std::string texString = env->Attribute("texture");
		sf::Texture* tex = ResourceManager::getInst().getTexture(texString);
		sf::Sprite* sprite = new sf::Sprite(*tex);

		mEnviroments.push_back(Enviroment(scenes,sprite));
	
		env = env->NextSiblingElement();
	}
}

std::string Cutscene::getMusic(){
	return mMusic;
}