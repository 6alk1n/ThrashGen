#include "ResourceManager.hpp"
#include <fstream>
namespace ThrashEngine
{
	TextureManager::TextureManager(Graphics* ptr)
	{
		m_graphics = ptr;
		m_colorkey = SDL_MapRGB(m_graphics->GetPixelFormat(), 0xff, 0xff, 0xff);
	}
	TextureManager::~TextureManager()
	{

	}
	SDL_Texture* TextureManager::GetTexture(std::string fileName)
	{
		auto it = m_textures.find(fileName);
		if (it != m_textures.end()) return it->second; //Texture was found

		//Check for file
		if (!ThrashEngine::is_file_exist(fileName.c_str())) return nullptr;//Texture doesn't exists

		//Load texture
		if (m_graphics == nullptr)return nullptr;
		SDL_Surface* m_surface = SDL_LoadBMP_RW(SDL_RWFromFile(fileName.c_str(), "rb"), 1);
		SDL_Texture* texture = m_graphics->CreateTexture(m_surface, m_colorkey);
		SDL_FreeSurface(m_surface); //free surface
		AddTexture(fileName, texture);
		return texture;
	}
	ResultState TextureManager::AddTexture(std::string fileName, SDL_Texture* texture)
	{

		auto it = m_textures.find(fileName);
		if (it != m_textures.end()) return ResultState::Fail; //Already exists with such name
		//Add texture to map
		m_textures.insert({ fileName,texture });
		return ResultState::Success;
	}
	ResultState TextureManager::ExistsTexture(std::string fileName)
	{
		auto it = m_textures.find(fileName);
		if (it != m_textures.end()) return ResultState::Success; //Already exists with such name
		return ResultState::Fail;
	}
	ResultState TextureManager::Clear()
	{
		m_textures.clear();
		return ResultState::Success;
	}
	ResultState TextureManager::SetColorKey(Uint32 col) //Set color key for loading textures
	{
		m_colorkey = col;
		return ResultState::Success;
	}

	SoundBufferManager::SoundBufferManager(){}
	SoundBufferManager::~SoundBufferManager(){}

	SoundBuffer* SoundBufferManager::GetSoundBuffer(std::string fileName)
	{
		auto it = m_soundBuffers.find(fileName);
		if (it != m_soundBuffers.end()) return it->second; //SoundBuffer was found

													   //Check for file
		if (!ThrashEngine::is_file_exist(fileName.c_str())) return nullptr;//SoundBuffer fileName doesn't exists

													   //Load SoundBuffer

		SoundBuffer* soundbuf = new SoundBuffer;
		soundbuf->LoadWav(fileName);
		AddSoundBuffer(fileName, soundbuf);
		return soundbuf;

	}


	ResultState SoundBufferManager::AddSoundBuffer(std::string fileName, SoundBuffer* buf) //Manualy add sound buffer to the map
	{
		auto it = m_soundBuffers.find(fileName);
		if (it != m_soundBuffers.end()) return ResultState::Fail; //Already exists with such name
															  //Add texture to map
		m_soundBuffers.insert({ fileName,buf });
		return ResultState::Success;
	}
}