#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <SFML\Graphics\Texture.hpp>
#include <SFML\Audio\SoundBuffer.hpp>
#include <string>
#include <map>

class ResourceManager{
public:

	sf::Texture* getTexture(std::string filePath);
	sf::SoundBuffer* getSoundBuffer(std::string filePath);
	static ResourceManager& getInst();

private:

	typedef std::map<std::string,sf::Texture*> TextureMap;
	TextureMap mTextureMap;
	
	typedef std::map<std::string,sf::SoundBuffer*> SoundBufferMap;
	SoundBufferMap mSoundBufferMap;

	ResourceManager& operator=(const ResourceManager&);
	ResourceManager(const ResourceManager&);
	ResourceManager();
	~ResourceManager();


};

#endif