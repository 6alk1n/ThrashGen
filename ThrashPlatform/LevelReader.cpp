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
bool LevelReader::ReadHeader(ThrashEngine::ObjectFactory* objFactory, ThrashEngine::AnimationObjectFactory* animFactory, 
	ThrashEngine::NpcFactory* npcFactory, std::string fileName, ThrashEngine::TextureManager* textures)
{
	//return true;
	std::fstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (!file) return false;
	int filetype;
	file.read((char*)&filetype, 4); //read File Type
	if (filetype == FileTypeHeader) //Check for header
	{
		//Read version
		int version;
		file.read((char*)&version, 4);

		//Read objecttype
		int objectType;
		file.read((char*)&objectType, 4);
		while (objectType != 0) //while not eof
		{
			//Read object name
			int nameLength;
			file.read((char*)&nameLength, 4);
			char* name = new char[nameLength];
			file.read(name, nameLength);
			name[nameLength] = 0;
			//Read size
			double size[2];
			file.read((char*)size, sizeof(double) * 2);

			//Read texture path
			int fileLength;
			file.read((char*)&fileLength, 4);
			char* filePath = new char[fileLength];
			file.read(filePath, fileLength);
			filePath[fileLength] = 0;
			//Read uv size
			ThrashEngine::Rectangle uvrect;
			file.read((char*)&uvrect, sizeof(ThrashEngine::Rectangle));

			//Read collideable and static
			int collideable, _static;
			file.read((char*)&collideable, 4);
			file.read((char*)&_static, 4);

			//Read properties
			int propsize;
			file.read((char*)&propsize, 4); 

			PropertyClass* property=new PropertyClass;
			if (propsize) {
				while (propsize--)
				{
					//read name and value size
					unsigned int propsize[2];
					file.read((char*)&propsize, 4 * 2);
					char* propname = new char(propsize[0]);
					file.read(propname, propsize[0]);
					propname[propsize[0]] = 0;

					char* value = new char(propsize[1]);
					file.read(value, propsize[1]);
					value[propsize[1]] = 0;

					//char* info = new char(propsize[2]);
			//		file.read(info, propsize[2]);
			//		info[propsize[2]] = 0;
					int type;
					file.read((char*)&type, 4);
					//Convert
					if (type == ThrashEngine::DOUBLE)
						property->Set(propname, StrToDouble(value));
					else property->Set(propname, std::string(value));
				}
			}
			//Create object
			if (objectType == VirtualLevelObject)
			{
				Object* newObject = new Object();
				newObject->m_pos.w = size[0];
				newObject->m_pos.h = size[1];
				newObject->m_active = true;
				newObject->m_collideable = collideable;
				newObject->m_static = _static;
				newObject->SetTexture(textures->GetTexture(filePath));
				newObject->m_debug = true;
				newObject->m_textureUV = uvrect;
				newObject->m_property = property;
				objFactory->AddNewObject(name, newObject);

			}
			else {
				//Read anim list name
				int animlistsize;
				file.read((char*)&animlistsize, 4);
				char* animlistname = new char[animlistsize];
				file.read(animlistname, animlistsize);
				animlistname[animlistsize] = 0;
				//Read anim uv rect
				ThrashEngine::Rectangle animuv;
				file.read((char*)&animuv, sizeof(ThrashEngine::Rectangle));
				if (objectType == VirtualLevelAnimationObject)
				{
					AnimationObject* newObject = new AnimationObject();
					newObject->m_pos.w = size[0];
					newObject->m_pos.h = size[1];
					newObject->m_active = true;
					newObject->m_collideable = collideable;
					newObject->m_static = _static;
					newObject->SetTexture(textures->GetTexture(filePath));
					newObject->m_debug = true;
					newObject->m_animlistname = animlistname;
					newObject->m_textureUV = uvrect;
					newObject->m_animUV = animuv;
					newObject->m_property = property;
					animFactory->AddNewAnimationObject(name, newObject);
				}
				if (objectType == VirtualLevelNPC)
				{
					NPC* newObject = new NPC();
					newObject->m_pos.w = size[0];
					newObject->m_pos.h = size[1];
					newObject->m_active = true;
					newObject->m_collideable = collideable;
					newObject->m_static = _static;
					newObject->SetTexture(textures->GetTexture(filePath));
					newObject->m_debug = true;
					newObject->m_animlistname = animlistname;
					newObject->m_textureUV = uvrect; 
					newObject->m_animUV = animuv;
					newObject->m_property = property;
					npcFactory->AddNewNpc(name, newObject);
				}
				
			}
			file.read((char*)&objectType, 4); //Read next object
		}

	}
	file.close();
	m_headers.push_back(fileName);
	return true;
}
bool LevelReader::SaveAnimationHeader(ThrashEngine::AnimationFactory* factory, std::string m_filePath)
{
	std::fstream file;
	file.open(m_filePath, std::ios::out | std::ios::binary);
	if (!file) return false;	
	if (!factory) return false;

	file.write((char*)&FileAnimationTypeHeader, sizeof(int)); //write file type
	file.write((char*)&AnimationHeaderVersion, sizeof(int)); //write version

	//Write all animations
	int animcount = factory->m_anims.size();
	file.write((char*)&animcount, sizeof(int));
	for (auto i = factory->m_anims.begin(); i != factory->m_anims.end(); i++)
	{
		//Write animation name
		int animnamesize = i->first.size();
		const char* animname = i->first.c_str();
		file.write((char*)&animnamesize, sizeof(int));
		file.write(animname, animnamesize);
		//Write animation data
		ThrashEngine::Animation anim = *i->second;
		file.write((char*)&anim, sizeof(ThrashEngine::Animation));
	}
	//Write animation lists
	int animlistcount = factory->m_animationInstances.size();
	file.write((char*)&animlistcount, sizeof(int));
	for (auto i = factory->m_animationInstances.begin(); i != factory->m_animationInstances.end(); i++)
	{
		//Write animation list name
		int animlistnamesize = i->first.size();
		const char* animlistname = i->first.c_str();
		file.write((char*)&animlistnamesize, sizeof(int));
		file.write(animlistname, animlistnamesize);
		//Write animation count
		int animationcount = i->second->m_anims.size();
		file.write((char*)&animationcount, sizeof(int));
		//Write animations
		for (auto n = i->second->m_anims.begin(); n != i->second->m_anims.end(); n++)
		{
			//Write animation list name
			int animnamesize = n->first.size();
			const char* animname = n->first.c_str();
			file.write((char*)&animnamesize, sizeof(int));
			file.write(animname, animnamesize);
		}
	}
	file.close();
	return true;
}
bool LevelReader::ReadAnimationHeader(ThrashEngine::AnimationFactory* factory, std::string m_filePath)
{
	std::fstream file;
	file.open(m_filePath, std::ios::in | std::ios::binary);
	if (!file) return false;
	if (!factory) return false;
	int filetype;
	file.read((char*)&filetype, sizeof(int)); //read file type
	if (filetype != FileAnimationTypeHeader)
	{
		file.close();
		return false;
	}
	int headerversion;
	file.read((char*)&headerversion, sizeof(int)); //read version

	int animcount;
	file.read((char*)&animcount, sizeof(int)); //read animcount

	while (animcount--)
	{
		//read animation
		int animnamesize;
		file.read((char*)&animnamesize, sizeof(int));
		char* animname = new char[animnamesize];
		file.read(animname, animnamesize);
		animname[animnamesize] = 0;
		ThrashEngine::Animation *animation=new ThrashEngine::Animation;
		file.read((char*)animation, sizeof(ThrashEngine::Animation));
		factory->AddAnimation(std::string(animname), animation);
	}
	//read animation lists
	int animlistcount;
	file.read((char*)&animlistcount, sizeof(int)); //read animcount
	while (animlistcount--)
	{
		//read animation list name
		int animlistnamesize;
		file.read((char*)&animlistnamesize, sizeof(int));
		char* animlistname = new char[animlistnamesize];
		file.read(animlistname, animlistnamesize);
		animlistname[animlistnamesize] = 0;
		factory->CreateInstance(animlistname);
		//read animation count
		int animationcount;
		file.read((char*)&animationcount, sizeof(int));
		while (animationcount--)
		{
			//read animation list name
			int animnamesize;
			file.read((char*)&animnamesize, sizeof(int));
			char* animname = new char[animnamesize];
			file.read(animname, animnamesize);
			animname[animnamesize] = 0;
			factory->AddAnimationToInstance(animlistname,animname);
		}
	}
	m_animheaders.push_back(m_filePath);
	return true;
}
bool LevelReader::SaveHeader(ThrashEngine::ObjectFactory* objFactory, ThrashEngine::AnimationObjectFactory* animFactory, 
	ThrashEngine::NpcFactory* npcFactory, std::string fileName, ThrashEngine::TextureManager* textures)
{
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::binary);
	if (!file) return false;

	file.write((char*)&FileTypeHeader, 4); //write file type
	file.write((char*)&HeaderVersion, 4); //write version

	//file.close();

	//write objFactory
	for (auto i = objFactory->m_objectInstances.begin(); i != objFactory->m_objectInstances.end(); i++)
	{
		//Write type of object
		file.write((char*)&VirtualLevelObject, 4);

		//Write object name
		int namesize = (i->first).size();
		file.write((char*)&namesize, 4);
		const char* name = i->first.c_str();
		file.write(name, namesize);
		//Write size
		file.write((char*)&i->second->m_pos.w,sizeof(double));
		file.write((char*)&i->second->m_pos.h,sizeof(double));

		std::string filepath = textures->FindTexture(i->second->m_texture);
		
		int filepathsize=filepath.size();
		file.write((char*)&filepathsize, 4);
		const char* filepathcstr = filepath.c_str();
		file.write(filepathcstr, filepathsize);
	
		file.write((char*)&i->second->m_textureUV, sizeof(ThrashEngine::Rectangle));

		int _collide = i->second->m_collideable;
		int _static = i->second->m_static;

		//Write collision
		file.write((char*)&_collide, 4);
		file.write((char*)&_static, 4);
		//Write property
		int propcount = i->second->m_property->m_property.size();
		file.write((char*)&propcount, 4);
		for (auto n = i->second->m_property->m_property.begin(); n != i->second->m_property->m_property.end(); n++)
		{
			int propnamesize = n->first.size();
			int propvaluesize = n->second.value.size();
		//	int propinfosize = n->second.info.size();
			file.write((char*)&propnamesize, 4);
			file.write((char*)&propvaluesize, 4); 
		//	file.write((char*)&propinfosize, 4);

			const char* propname = n->first.c_str();
			file.write(propname, propnamesize);
			
			const char* propvalue = n->second.value.c_str();
			file.write(propvalue, propvaluesize);	

		//	const char* propinfo = n->second.info.c_str();
		//	file.write(propinfo, propinfosize);

			file.write((char*)n->second.type, 4);
		}
	}
	//write animFactory
	for (auto i = animFactory->m_animobjectInstances.begin(); i != animFactory->m_animobjectInstances.end(); i++)
	{
		//Write type of object
		file.write((char*)&VirtualLevelAnimationObject, 4);

		//Write object name
		int namesize = (i->first).size();
		file.write((char*)&namesize, 4);
		const char* name = i->first.c_str();
		file.write(name, namesize);
		//Write size
		file.write((char*)&i->second->m_pos.w, sizeof(double));
		file.write((char*)&i->second->m_pos.h, sizeof(double));		
		
		std::string filepath = textures->FindTexture(i->second->m_texture);

		int filepathsize = filepath.size();
		file.write((char*)&filepathsize, 4);
		const char* filepathcstr = filepath.c_str();
		file.write(filepathcstr, filepathsize);

		file.write((char*)&i->second->m_textureUV, sizeof(ThrashEngine::Rectangle));
		//Write collision
		file.write((char*)&i->second->m_collideable, 4);
		file.write((char*)&i->second->m_static, 4);
		//Write property
		int propcount = i->second->m_property->m_property.size();
		file.write((char*)&propcount, 4);
		for (auto n = i->second->m_property->m_property.begin(); n != i->second->m_property->m_property.end(); n++)
		{
			int propnamesize = n->first.size();
			int propvaluesize = n->second.value.size();
			//	int propinfosize = n->second.info.size();
			file.write((char*)&propnamesize, 4);
			file.write((char*)&propvaluesize, 4);
			//	file.write((char*)&propinfosize, 4);

			const char* propname = n->first.c_str();
			file.write(propname, propnamesize);

			const char* propvalue = n->second.value.c_str();
			file.write(propvalue, propvaluesize);

			//	const char* propinfo = n->second.info.c_str();
			//	file.write(propinfo, propinfosize);

			file.write((char*)n->second.type, 4);
		}
		//Write animname
		int animlistsize = i->second->m_animlistname.size();
		file.write((char*)&animlistsize, 4);
		const char* animlistname = i->second->m_animlistname.c_str();
		file.write(animlistname, animlistsize);
		//Write animUV
		file.write((char*)&i->second->m_animUV, sizeof(ThrashEngine::Rectangle));
	}//write npcFactory
	for (auto i = npcFactory->m_npcInstances.begin(); i != npcFactory->m_npcInstances.end(); i++)
	{
		//Write type of object
		file.write((char*)&VirtualLevelNPC, 4);

		//Write object name
		int namesize = (i->first).size();
		file.write((char*)&namesize, 4);
		const char* name = i->first.c_str();
		file.write(name, namesize);
		//Write size
		file.write((char*)&i->second->m_pos.w, sizeof(double));
		file.write((char*)&i->second->m_pos.h, sizeof(double));

		std::string filepath = textures->FindTexture(i->second->m_texture);

		int filepathsize = filepath.size();
		file.write((char*)&filepathsize, 4);
		const char* filepathcstr = filepath.c_str();
		file.write(filepathcstr, filepathsize);

		file.write((char*)&i->second->m_textureUV, sizeof(ThrashEngine::Rectangle));

		//Write collision
		file.write((char*)&i->second->m_collideable, 4);
		file.write((char*)&i->second->m_static, 4);
		//Write property
		int propcount = i->second->m_property->m_property.size();
		file.write((char*)&propcount, 4);
		for (auto n = i->second->m_property->m_property.begin(); n != i->second->m_property->m_property.end(); n++)
		{
			int propnamesize = n->first.size();
			int propvaluesize = n->second.value.size();
			//	int propinfosize = n->second.info.size();
			file.write((char*)&propnamesize, 4);
			file.write((char*)&propvaluesize, 4);
			//	file.write((char*)&propinfosize, 4);

			const char* propname = n->first.c_str();
			file.write(propname, propnamesize);

			const char* propvalue = n->second.value.c_str();
			file.write(propvalue, propvaluesize);

			//	const char* propinfo = n->second.info.c_str();
			//	file.write(propinfo, propinfosize);

			file.write((char*)&n->second.type, sizeof(n->second.type));
		}		
		//Write animlist name
		int animlistsize = i->second->m_animlistname.size();
		file.write((char*)&animlistsize, 4);
		const char* animlistname = i->second->m_animlistname.c_str();
		file.write(animlistname, animlistsize);		
		//Write animUV
		file.write((char*)&i->second->m_animUV, sizeof(ThrashEngine::Rectangle));
	}
	int endfile = 0;
	file.write((char*)&endfile, 4);
	file.close();
	return true; 
}
bool LevelReader::ReadHeader(ThrashEngine::ObjectManager* map, std::string fileName, ThrashEngine::TextureManager* textureMan)
{
/*	std::fstream file;
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
	return true;*/
	return true;
}

bool LevelReader::SaveLevel(ThrashEngine::ObjectManager* world, std::string fileName)
{
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::binary);
	if (!file) return false;
	file.write((char*)&FileLevel, sizeof(int));
	file.write((char*)&LevelVersion, sizeof(int));

	unsigned int animheadercount = m_animheaders.size();
	file.write((char*)&animheadercount, sizeof(int));
	for (auto i = m_animheaders.begin(); i != m_animheaders.end(); i++)
	{
		unsigned int filepathsize = i->size();
		file.write((char*)&filepathsize, sizeof(int));
		
		file.write((*i).c_str(), filepathsize);
	}

	//Write object headers
	unsigned int headercount = m_headers.size();
	file.write((char*)&headercount, sizeof(int));
	for (auto i = m_headers.begin(); i != m_headers.end(); i++)
	{
		unsigned int filepathsize = i->size();
		file.write((char*)&filepathsize, sizeof(int));
		file.write((*i).c_str(), filepathsize);
	}
	
	unsigned int objectCount = world->objects.size();

	struct _objectread
	{
		unsigned int virtual_level;
		unsigned int objectnamesize;
		char* objectname;
		double posx;
		double posy;
		double objectw;
		double objecth;
	};

	for (auto i = world->objects.begin(); i != world->objects.end(); i++)
	{
		unsigned int vlvl = (*i)->GetVirtualizationLevel();
		file.write((char*)&vlvl, sizeof(int));
		unsigned int objecttypename = (*i)->m_objectName.size();
		file.write((char*)&objecttypename, sizeof(int));
		file.write((*i)->m_objectName.c_str(), objecttypename);
		double size[4];
		size[0] = (*i)->m_pos.x;
		size[1] = (*i)->m_pos.y;
		size[2] = (*i)->m_pos.w;
		size[3] = (*i)->m_pos.h;
		file.write((char*)&size, sizeof(double) * 4);
	}
	//leveldata property
	if (m_lvlproperties.size()) file.write((char*)&LevelProperty, sizeof(int));
	for (auto i = m_lvlproperties.begin(); i != m_lvlproperties.end(); i++)
	{
		file.write((char*)&i->objid, sizeof(int));
		unsigned int namesize = i->name.size();
		unsigned int valuesize = i->prop.value.size();
		file.write((char*)&namesize, sizeof(int));
		file.write((char*)&valuesize, sizeof(int));
		const char* name = i->name.c_str();
		const char* value = i->prop.value.c_str();
		file.write(name, namesize);
		file.write(value, valuesize);
		if (m_lvlproperties.size()) file.write((char*)&LevelProperty, sizeof(int));
	}
	//eof
	unsigned int zero = 0;
	file.write((char*)&zero, sizeof(int));
	file.write((char*)&zero, sizeof(int));
	file.close();
	/*
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
		//obj.id = i[0]->GetID();
		obj.id = 0;
		obj.x = i[0]->m_pos.x;
		obj.y = i[0]->m_pos.y;
		obj.w = i[0]->m_pos.w;
		obj.h = i[0]->m_pos.h;
		file.write((char*)&obj, sizeof(ObjectData));//Write object into file
		if (((Object*)i[0])->GetVirtualState() == VirtualLevelNPC)
		{
			auto npc = (NPC*)*i;
			int propsize = sizeof(npc->m_property);
			propsize = npc->m_property.size();
			file.write((char*)&propsize, sizeof(int));//Write property size
			file.write((char*)&npc->m_property, sizeof(npc->m_property));
		}
		else
		{
			int nul = 0;
			file.write((char*)&nul , sizeof(int));//Write property size
		}
	}
	file.close();
	return true;*/
	return true;
}


bool LevelReader::ReadLevel(ThrashEngine::ObjectManager* world, ThrashEngine::AnimationFactory* animfactory, ThrashEngine::ObjectFactory* objfactory, ThrashEngine::AnimationObjectFactory* animobjfactory, ThrashEngine::NpcFactory* npcfactory, std::string fileName, ThrashEngine::TextureManager* textures)
{
	//Read level info
	std::fstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (!file) return false;
	unsigned int filetype;
	file.read((char*)&filetype, sizeof(int));
	if (filetype != FileLevel)
	{
		file.close();
		return false;
	}
	unsigned int version;
	file.read((char*)&version, sizeof(int));
	if (version > LevelVersion)
	{
		file.close();
		return false;
	}
	//Read animations
	unsigned int animheadercount;
	file.read((char*)&animheadercount, sizeof(int));
	while (animheadercount--)
	{
		unsigned int animfilesize;
		file.read((char*)&animfilesize, sizeof(int));
		char* animfile = new char[animfilesize];
		file.read(animfile, animfilesize);
		animfile[animfilesize] = 0;
		if (!ReadAnimationHeader(animfactory, animfile))
		{
			file.close();
			return false;
		}
	}
	//Read object headers
	unsigned int objheadercount;
	file.read((char*)&objheadercount, sizeof(int));
	while (objheadercount--)
	{
		unsigned int objfilesize;
		file.read((char*)&objfilesize, sizeof(int));
		char* objfile = new char[objfilesize];
		file.read(objfile, objfilesize);
		objfile[objfilesize] = 0;
		if (!ReadHeader(objfactory,animobjfactory,npcfactory,objfile,textures))
		{
			file.close();
			return false;
		}
		//delete objfile;
	}	

	//Unite object headers with animations
	animobjfactory->SetAnimations(animfactory);
	npcfactory->SetAnimations(animfactory);
	//Read objects
	unsigned int objectcount;
	file.read((char*)&objectcount, sizeof(int));
	while (objectcount--)
	{
		unsigned int objtype[2];
		file.read((char*)&objtype, sizeof(int) * 2);
		unsigned int objnamesize;
		file.read((char*)&objnamesize, sizeof(int));
		char* objname = new char[objnamesize];
		file.read(objname, objnamesize);
		objname[objnamesize] = 0;
		Object* newobj;
		if (objtype[0] == VirtualLevelObject)
			newobj = objfactory->CreateObject(objname);
		if (objtype[0] == VirtualLevelAnimationObject)
			newobj = animobjfactory->CreateAnimationObject(objname);
		if (objtype[0] == VirtualLevelNPC)
			newobj = npcfactory->CreateNpc(objname);
		file.read((char*)&newobj->m_pos, sizeof(double) * 4);
	//	delete objname;
		world->AddObject(newobj);
	}

	//Read all world data
	unsigned int worlddata[2];
	file.read((char*)&worlddata, sizeof(int) * 2);
	while (worlddata[0] && worlddata[1]) //while not 0 0
	{
		if (worlddata[0] == LevelProperty)
		{
			//read sizes
			unsigned int propnamesize;
			file.read((char*)&propnamesize, sizeof(int));	
			unsigned int propvaluesize;
			file.read((char*)&propvaluesize, sizeof(int));
			//read property
			char* propname = new char[propnamesize];
			file.read(propname, propnamesize);
			propname[propnamesize] = 0;
			char* value = new char[propvaluesize];
			file.read(value, propvaluesize);
			value[propvaluesize] = 0;
			int type;
			file.read((char*)&type, 4);

			Object* ptr = world->Get(worlddata[1]); //get object
			//Set property
			if (type == ThrashEngine::DOUBLE)
				ptr->m_property->Set(propname, StrToDouble(value));
			else ptr->m_property->Set(propname, std::string(value));
		}
		//Read next data
		unsigned int worlddata[2];
		file.read((char*)&worlddata, sizeof(int) * 2);
	}
	return true;
}

bool LevelReader::LoadLevel(ThrashEngine::ObjectManager* world, std::string fileName, ThrashEngine::TextureManager* textures)
{
	/*
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
		//	NPC* npc = CreateNPC(obj.id, world);
			//file.read((char*)&npc->m_property, sizeof(NPCProperties));
			//npc->m_pos = Vector(obj.x, obj.y);
			//npc->SetSize(obj.w, obj.h);
		}
		else {
			ThrashEngine::Object* ob = world->CreateObject(obj.id);
			ob->m_pos = Vector(obj.x, obj.y);
			ob->SetSize(obj.w, obj.h);
		}
	}
	return true;*/
	return true;
}
void LevelReader::AddFreeSave(ThrashEngine::Sprite* spr)
{
	m_freesaveobjects.push_back(spr);
}

void LevelReader::AddPropertyToLevel(unsigned int id, Property prop, std::string name)
{
	LevelDataProperty property;
	property.objid = id;
	property.prop = prop;
	property.name = name;
	m_lvlproperties.push_back(property);
}
void LevelReader::AddPropertyToLevel(Object* obj)
{
	for (auto i = obj->m_property->m_property.begin(); i != obj->m_property->m_property.end(); i++)
	{
		LevelDataProperty property;
		property.objid = obj->m_objectID;
		property.prop = i->second;
		property.name = i->first;
		m_lvlproperties.push_back(property);
	}

}
void LevelReader::ClearPropertyLevel()
{
	m_lvlproperties.clear();
}