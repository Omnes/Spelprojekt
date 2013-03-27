#include "OptionsMeny.h"
#include "WindowManager.h"
#include "EventManager.h"
#include "ResourceManager.h"

OptionsMeny::OptionsMeny()
	: mApplyButton(sf::Vector2f(910,590),"Resources/Menu/GameOverMenu/MenuButton.png","Resources/Sound/Menu/Menu_forward.wav",this){
	mCheckboxes.push_back(new Checkbox(sf::Vector2f(850,165),"Resolution","fullscreen"));
	mCheckboxes.push_back(new Checkbox(sf::Vector2f(230,475),"Sound","muted"));
	mCheckboxes.push_back(new Checkbox(sf::Vector2f(850,215),"Tutorial","play"));


	//ändra till vector sen.
	mOptionSliders.push_back(new OptionSlider(sf::Vector2f(50,180), "Sound", "musicVolume"));
	mOptionSliders.push_back(new OptionSlider(sf::Vector2f(50,280), "Sound", "soundVolume"));
	mOptionSliders.push_back(new OptionSlider(sf::Vector2f(50,380), "Sound", "voiceVolume"));

	mMusic = "Resources/Sound/Music/Title_Screen_";


	mBackground.setTexture(*ResourceManager::getInst().getTexture("Resources/Menu/OptionsMenu/bakgrund_optionsmeny.png"));
	readText();
}

OptionsMeny::~OptionsMeny(){
	while(!mCheckboxes.empty()){
		delete mCheckboxes.back();
		mCheckboxes.pop_back();
	}
}

void OptionsMeny::update(){
	for (std::vector<Checkbox*>::iterator i = mCheckboxes.begin(); i != mCheckboxes.end(); i++){
		(*i)->update();
	}
	mApplyButton.update();

	//vector med sliders
	for(OptionSliders::iterator i = mOptionSliders.begin(); i != mOptionSliders.end(); i++){
		(*i)->update();
	}

}

void OptionsMeny::render(){
	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	window->draw(mBackground);

	for (std::vector<Checkbox*>::iterator i = mCheckboxes.begin(); i != mCheckboxes.end(); i++){
		(*i)->render(); 
	}
	window->draw(mApplyButton.getSprite());

	//vector med sliders
	for(OptionSliders::iterator i = mOptionSliders.begin(); i != mOptionSliders.end(); i++){
		(*i)->render();
	}

	for(OptionText::iterator i = mOptionText.begin(); i != mOptionText.end(); i++){
		window->draw((*i));
	}

}

std::string OptionsMeny::getMusic(){
	return mMusic;
}

void OptionsMeny::saveSettings(){

	for(std::vector<Checkbox*>::iterator i = mCheckboxes.begin(); i != mCheckboxes.end();i++){
		(*i)->saveSetting();
	}

	//gör om till vector
	for(OptionSliders::iterator i = mOptionSliders.begin(); i != mOptionSliders.end(); i++){
		(*i)->saveSettings();
	}

	EventManager::getInst().addEvent("goBackToStartFromOptions");


}

void OptionsMeny::readText(){
	tinyxml2::XMLDocument doc;

	doc.LoadFile("Resources/Data/Menu/OptionsMenu/OptionText.xml");

	tinyxml2::XMLElement *elm = doc.FirstChildElement("Text");

	while(elm  != 0){
		mText.setString(elm->GetText());
		mText.setPosition(sf::Vector2f(elm->FloatAttribute("x"), elm->FloatAttribute("y")));
		mText.setFont(FontMaster::sFont);
		mText.setColor(sf::Color(0,0,0));
		mText.setCharacterSize(elm->IntAttribute("size"));
		mOptionText.push_back(mText);
		elm = elm->NextSiblingElement();
	}
}