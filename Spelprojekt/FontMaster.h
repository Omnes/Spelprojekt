#ifndef FONTMASTER
#define FONTMASTER
#include <SFML\Graphics\Font.hpp>
#include "tinyxml2.h"

class FontMaster{
public:

	static sf::Font sFont;

	static void loadFonts(){

		tinyxml2::XMLDocument doc;
		doc.LoadFile("Resources/Data/Settings.xml");

		sFont.loadFromFile(doc.FirstChildElement("Font")->Attribute("filepath"));
	};
	

};

#endif