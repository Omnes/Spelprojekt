#include "Cutscene.h"
#include "Scene.h"
#include "WindowManager.h"
#include <SFML\Window\Keyboard.hpp>
#include "tinyxml2.h"
#include "ResourceManager.h"


Cutscene::Cutscene(std::string file){
	loadFromFile(file);
	mCurrentEnviroment = 0;
	mCurrentScene = 0;

	
}

Cutscene::~Cutscene(){

	while(!mEnviroments.empty()){
		while(!mEnviroments.back().first.empty()){
			delete mEnviroments.back().first.back();
			mEnviroments.back().first.pop_back();
		}
		delete mEnviroments.back().second;
		mEnviroments.pop_back();
	}
}

void Cutscene::goToNext(){
	
	if(mEnviroments[mCurrentEnviroment].first.size() < mCurrentScene + 2){
		mCurrentScene ++;
	}else{
		mCurrentScene = 0;
		if(mEnviroments.size() < mCurrentEnviroment + 2){
			mCurrentEnviroment ++;
		}else{
			//end cutscene yes.
		}
	}
	mEnviroments[mCurrentEnviroment].first[mCurrentScene]->play();
}

void Cutscene::update(){
	if(mEnviroments[mCurrentEnviroment].first[mCurrentScene]->isCompleted()){
		goToNext();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		//end cutscene yes.
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

			sf::Text text;

			text.setString(sce->FirstChildElement("Text")->GetText());
			float tx = sce->FirstChildElement("Text")->FloatAttribute("x");
			float ty = sce->FirstChildElement("Text")->FloatAttribute("y");
			text.setPosition(tx,ty);

			std::string voice = sce->FirstChildElement("Voice")->Attribute("file");

			std::string texString = sce->FirstChildElement("Image")->Attribute("texture");
			sf::Texture* tex = ResourceManager::getInst().getTexture(texString);
			sf::Sprite* sprite = new sf::Sprite(*tex);
			float sx = sce->FirstChildElement("Image")->FloatAttribute("x");
			float sy = sce->FirstChildElement("Image")->FloatAttribute("y");
			sprite->setPosition(sx,sy);

			
			
			Scene* scene = new Scene(sprite,voice,text);
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