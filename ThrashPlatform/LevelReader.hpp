#pragma once
#include <Engine/Core.hpp>
#include <Engine/TileMap.hpp>
#include <Engine/ResourceManager.hpp>
#include <vector>
struct ObjectData
{
	int id;
	double x;
	double y;
	double w;
	double h;
};

class LevelReader
{
public:
	LevelReader();
	~LevelReader();
	bool ReadHeader(ThrashEngine::TileMap*,std::string, ThrashEngine::TextureManager*);
	bool SaveLevel(ThrashEngine::TileMap*,std::string);
	bool LoadLevel(ThrashEngine::TileMap*, std::string, ThrashEngine::TextureManager*);
	void AddFreeSave(ThrashEngine::Sprite*);
protected:
	std::vector<ThrashEngine::Sprite*> m_freesaveobjects;
};