#include "InnerBeastArrow.h"
#include "ResourceManager.h"
#include "WindowManager.h"


InnerBeastArrow::InnerBeastArrow(sf::Vector2f pos, std::string img) : mPosition(pos), mCurrentImage(0){
	mTexture = (ResourceManager::getInst().getTexture(img));
	mSprite.setTexture(*mTexture);
	mSprite.setPosition(mPosition);
	mRectangle = sf::IntRect(0,0, mTexture->getSize().x/10, mTexture->getSize().y);
	mSprite.setTextureRect(mRectangle);
	mSprite.setOrigin(mTexture->getSize().x/20, mTexture->getSize().y/2);
}

InnerBeastArrow::~InnerBeastArrow(){

}


void InnerBeastArrow::update(){

	sf::RenderWindow* window = WindowManager::getInst().getWindow();

	sf::Vector2f mousePosition = WindowManager::getInst().getWindow()->convertCoords(sf::Mouse::getPosition(*WindowManager::getInst().getWindow()),WindowManager::getInst().getWindow()->getDefaultView());
	
	if(mSprite.getGlobalBounds().contains(mousePosition)){		
	
		mCurrentImage=1;	
	}

	else{

		mCurrentImage=0;
	}

	mRectangle.left = mRectangle.width*mCurrentImage;
	mSprite.setTextureRect(mRectangle);
}

sf::Sprite& InnerBeastArrow::getSprite(){

	return mSprite;
}
