#include "ResourceManager.h"


ResourceManager::ResourceManager(){

}

ResourceManager::~ResourceManager(){

}

ResourceManager& ResourceManager::getInst(){
	static ResourceManager instance;

	return instance;
}

sf::Texture* ResourceManager::getTexture(std::string filePath){
	//kolla om texturen finns
	TextureMap::iterator i;
	i = mTextureMap.find(filePath);
	//om inte laddad, se till att ladda in den och returnera
	if(i == mTextureMap.end()){
		sf::Texture* tex = new sf::Texture;
		tex->loadFromFile(filePath);
		mTextureMap[filePath] = tex;
		return tex;
	}
	//om den hittades returnera den
	return mTextureMap[filePath];
}

sf::SoundBuffer* ResourceManager::getSoundBuffer(std::string filePath){

	SoundBufferMap::iterator i;
	i = mSoundBufferMap.find(filePath);
	if(i == mSoundBufferMap.end()){
		sf::SoundBuffer* sb = new sf::SoundBuffer;
		sb->loadFromFile(filePath);
		mSoundBufferMap[filePath] = sb;
		return sb;
	}
	return mSoundBufferMap[filePath];

}
