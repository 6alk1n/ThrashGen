#include "LevelReader.hpp"
#include <Engine/Npc.hpp>
#include <fstream>
using namespace ThrashEngine;
LevelReader::LevelReader()
{

}
LevelReader::~LevelReader()
{

}
bool LevelReader::ReadHeader(ThrashEngine::TileMap* map, std::string fileName, ThrashEngine::TextureManager* textureMan)
{
	std::fstream file;
	file.open(fileName, std::ios::in);
	if (!file) return false;
	std::string input;
	std::string texturePath;
	std::getline(file, input);//Read first line
	ThrashEngine::SpriteHeader* newHeader;
	while (file)
	{
		newHeader = new ThrashEngine::SpriteHeader;
		newHeader->m_SpriteName = input;
		std::getline(file, input);//Read width line
		newHeader->m_width = ThrashEngine::StrToDouble(input);
		std::getline(file, input);//Read height line
		newHeader->m_height = ThrashEngine::StrToDouble(input);
		std::getline(file, texturePath);//Read filePath to new texture
		newHeader->m_texture=textureMan->GetTexture(texturePath);
		std::getline(file, input);//Read u_start line
		newHeader->m_u = ThrashEngine::StrToDouble(input);
		std::getline(file, input);//Read v_start line
		newHeader->m_v = ThrashEngine::StrToDouble(input);;
		std::getline(file, input);//Read u_end line
		newHeader->m_uend = ThrashEngine::StrToDouble(input);
		std::getline(file, input);//Read v_end line
		newHeader->m_vend = ThrashEngine::StrToDouble(input);
		if (newHeader->m_texture == nullptr) std::cout << "Texture was not found!";
		map->AddHeader(newHeader);
		std::getline(file, input);//Read new header name or EOF
	}
	map->AddHeaderFile(fileName);
	file.close();
	return true;
}

bool LevelReader::SaveLevel(ThrashEngine::TileMap* world, std::string fileName)
{
	std::fstream file;
	file.open(fileName, std::ios::out|std::ios::binary);
	if (!file) return false;
	std::vector<std::string>* headers = world->GetHeaderFiles();
	//Write header count
	int headcount = headers->size();
	file.write((char*)&headcount, sizeof(int));
	//Write headers
	for (auto i = headers->begin(); i != headers->end(); i++)
	{
		int pathSize = i[0].size(); 
		file.write((char*)&pathSize, sizeof(int)); //write size of header fileName
		file.write(i[0].c_str(), pathSize);//write headerfile
	}
	//Write level data
	int count = world->GetObjectCount()-m_freesaveobjects.size();
	file.write((char*)&count, sizeof(int)); //write count of objects
	//Write objects
	for (auto i = world->GetSpritePtr()->begin(); i != world->GetSpritePtr()->end(); i++)
	{
		bool found = false;
		for (auto n = m_freesaveobjects.begin(); n != m_freesaveobjects.end(); n++)
		{
			if (*i == *n)
			{
				found = true; break; 
			}
		}
			//if (*n = i) continue;
		if (found) continue;
		ObjectData obj;
		obj.id = i[0]->GetID();
		obj.x = i[0]->GetX();
		obj.y = i[0]->GetY();
		obj.w = i[0]->GetWidth();
		obj.h = i[0]->GetHeight();
		file.write((char*)&obj, sizeof(ObjectData));//Write object into file
		if (((Object*)i[0])->GetVirtualState() == VirtualStateNPC)
		{
			auto npc = (NPC*)*i;
			int propsize = sizeof(npc->properties);
			propsize = npc->m_property.size();
			file.write((char*)&propsize, sizeof(int));//Write property size
			file.write((char*)&npc->m_property, sizeof(npc->properties));
		}
		else
		{
			int nul = 0;
			file.write((char*)&nul , sizeof(int));//Write property size
		}
	}
	file.close();
	return true;
}

bool LevelReader::LoadLevel(ThrashEngine::TileMap* world, std::string fileName, ThrashEngine::TextureManager* textures)
{
	std::fstream file;
	file.open(fileName,std::ios::in|std::ios::binary);
	if (!file) return false;
	int count;
	file.read((char*)&count, sizeof(int)); //read header count
	//read headers
	for (int i = 0; i < count; i++)
	{
		int filePathsize;
		file.read((char*)&filePathsize, sizeof(int)); //read header count
		char* filePath=new char[filePathsize+1];
		filePath[filePathsize] = 0;
		file.read((char*)filePath, filePathsize);//read header filePath
		//read new header into world
		ReadHeader(world, filePath, textures);
		delete []filePath; //delete leak memory
	}
	//read level data
	file.read((char*)&count, sizeof(int)); //read object count
	for (int i = 0; i < count; i++)
	{
		ObjectData obj;
		file.read((char*)&obj, sizeof(ObjectData)); //read object
		int propsize;
		file.read((char*)&propsize, sizeof(int));
		if (propsize)
		{
			NPC* npc = CreateNPC(obj.id, world);
			file.read((char*)&npc->properties, sizeof(NPCProperties));
			npc->SetPos(obj.x, obj.y);
			npc->SetSize(obj.w, obj.h);
		}
		else {
			ThrashEngine::Object* ob = world->CreateObject(obj.id);
			ob->SetPos(obj.x, obj.y);
			ob->SetSize(obj.w, obj.h);
		}
	}
	return true;
}
void LevelReader::AddFreeSave(ThrashEngine::Sprite* spr)
{
	m_freesaveobjects.push_back(spr);
}
