#pragma once
#include <Engine/Core.hpp>
#include <Engine/ObjectManager.hpp>
#include <Engine/ResourceManager.hpp>
#include <vector>
#include <Engine/AnimationFactory.hpp>
#include <Engine/ObjectFactory.hpp>
using namespace ThrashEngine;
/*struct ObjectData
{
	int id;
	double x;
	double y;
	double w;
	double h;
};*/
struct LevelDataProperty
{
	unsigned int objid;
	std::string name;
	Property prop;
};

const int FileTypeHeader=1;
const int FileAnimationTypeHeader = 2;
const int FileLevel = 3;

const int HeaderVersion = 0x0001;
const int AnimationHeaderVersion = 0x0001;
const int LevelVersion = 0x0001;

const int LevelData = 1;
const int LevelProperty = 2;


class LevelReader
{
public:
	LevelReader();
	~LevelReader();
	bool ReadHeader(ThrashEngine::ObjectFactory*, ThrashEngine::AnimationObjectFactory*, ThrashEngine::NpcFactory*, std::string, ThrashEngine::TextureManager*);
	bool SaveHeader(ThrashEngine::ObjectFactory*, ThrashEngine::AnimationObjectFactory*, ThrashEngine::NpcFactory*, std::string, ThrashEngine::TextureManager*);
	bool SaveAnimationHeader(ThrashEngine::AnimationFactory*, std::string m_filePath);
	bool ReadAnimationHeader(ThrashEngine::AnimationFactory*, std::string m_filePath);
	bool SaveLevel(ThrashEngine::ObjectManager*, std::string);
	bool ReadLevel(ThrashEngine::ObjectManager*, ThrashEngine::AnimationFactory*,ThrashEngine::ObjectFactory*, ThrashEngine::AnimationObjectFactory*, ThrashEngine::NpcFactory*, std::string, ThrashEngine::TextureManager*);
	
	void AddPropertyToLevel(unsigned int, Property,std::string);
	void AddPropertyToLevel(Object*);
	void ClearPropertyLevel();
	
	//old
	bool ReadHeader(ThrashEngine::ObjectManager*,std::string, ThrashEngine::TextureManager*);
	bool LoadLevel(ThrashEngine::ObjectManager*, std::string, ThrashEngine::TextureManager*);
	void AddFreeSave(ThrashEngine::Sprite*);
protected:
	std::vector<ThrashEngine::Sprite*> m_freesaveobjects;
	std::vector<std::string> m_headers;
	std::vector<std::string> m_animheaders;
	std::vector<LevelDataProperty> m_lvlproperties;
};