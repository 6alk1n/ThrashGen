#pragma once
#include "Graphics.hpp"
#include "AudioMaster.hpp"
/************************
ResourceManager.hpp
Contains all textures. Texture container.
*************************/
#include <map>
namespace ThrashEngine
{
	class TextureManager
	{
	public:
		TextureManager(Graphics*); 
		~TextureManager();
		SDL_Texture* GetTexture(std::string); //Returns texture by it's relative path (if texture was not found in map, it will load it from disk)
		ResultState AddTexture(std::string, SDL_Texture*); //Manualy add texture to the map
		ResultState ExistsTexture(std::string); //Check if texture is in map
		ResultState Clear();//Delete all textures
		ResultState SetColorKey(Uint32); //Set color key for loading textures

	private:
		std::map<std::string, SDL_Texture*> m_textures;
		Graphics* m_graphics;
		Uint32 m_colorkey;
	};

	class SoundBufferManager
	{
	public:
		SoundBufferManager();
		~SoundBufferManager();
		SoundBuffer* GetSoundBuffer(std::string);
		ResultState AddSoundBuffer(std::string, SoundBuffer*); //Manualy add sound buffer to the map

	private:

		std::map<std::string, SoundBuffer*> m_soundBuffers;

	};
}