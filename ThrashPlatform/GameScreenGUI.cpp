#include "GameScreenGUI.hpp"
using namespace ThrashEngine;
#include <Engine/Utility.hpp>
void* m_exitFunc(void* packet)
{
	GameScreen* ptr = (GameScreen*)packet;
	ptr->OnShutdown();
	return nullptr;
}

#ifndef OFN_OVERWRITEPROMPT
#define OFN_OVERWRITEPROMPT 0x00000002
#endif
#ifndef OFN_FILEMUSTEXIST 
#define OFN_FILEMUSTEXIST 0x00001000
#endif

void* m_saveFunc(void* packet)
{
	//#ifdef _Debug
	std::string file = ThrashEngine::Utility::DialogSaveFile("Save Level", "Level Files\0 * .lvl\0", OFN_OVERWRITEPROMPT);

	file += ".lvl";
	if (file.size()) {
		GameScreen* ptr = (GameScreen*)packet;
		ptr->m_levelreader.AddPropertyToLevel(ptr->m_player);
		ptr->m_levelreader.SaveLevel(ptr->m_world, file);	
		ptr->m_levelreader.ClearPropertyLevel();
	}
	return nullptr;
}

void* m_openFunc(void* packet)
{
	//#ifdef _Debug
	std::string file = ThrashEngine::Utility::DialogOpenFile("Open Level", "Level Files\0 * .lvl\0", OFN_FILEMUSTEXIST);
	//file += ".lvl";
	if (file.size()) {
		GameScreen* ptr = (GameScreen*)packet;
		ptr->m_world->Clear();
		//ptr->m_world->m
		ptr->m_levelreader.LoadLevel(ptr->m_world, file, ptr->m_textures);
/*		ptr->m_player = CreateNPC("Player", ptr->m_world);
		ptr->m_player->properties.armor = 0;
		ptr->m_player->properties.damage = 3;
		ptr->m_player->properties.maxhp = 50;
		ptr->m_player->properties.hp = 50;
		ptr->m_player->properties.interactionColdDown = 60;
		ptr->m_player->SetUVCell(46, 50);*/
		ptr->AddAnimaton(ptr->m_player);

		ptr->m_player->m_property->Set("CanJump", 0);
		ptr->m_player->m_pos = Vector(50, 50);
		ptr->m_player->EnableAI(false);
		//ptr->m_player->properties.fraction = 1;
		ptr->m_player->m_property->Set("CanJump", 1);
		ptr->m_player->m_property->Set("TimeBetweenJump", 60.0);
	//	ptr->m_player->SetVirtualState(VirtualStatePlayer);

		//ptr->m_player->SetProperty("CanJump", true);

	}
	return nullptr;
}
void* m_editFunc(void* packet)
{
	GameScreen* ptr = (GameScreen*)packet;
	ptr->m_levelEditorState = !ptr->m_levelEditorState;
	if (ptr->m_levelEditorState)
	{
		ptr->m_saveButton.m_active=true;
		ptr->m_openButton.m_active=false;
		for (int i = 0; i < ptr->m_guiparams.LevelEditorCellColumn*ptr->m_guiparams.LevelEditorCellRow; i++)
			ptr->LevelEditorSelectorButtons[i].m_active=true;
		ptr->m_SpinButtonWidth.m_active=true;
		ptr->m_SpinButtonHeight.m_active=true;
	}
	else
	{
		ptr->m_saveButton.m_active=false;
		ptr->m_openButton.m_active=true;
		for (int i = 0; i <ptr->m_guiparams.LevelEditorCellColumn*ptr->m_guiparams.LevelEditorCellRow; i++)
			ptr->LevelEditorSelectorButtons[i].m_active=false;
		ptr->m_SpinButtonWidth.m_active=false;
		ptr->m_SpinButtonHeight.m_active=false;
	}
	SoundSource* source = new SoundSource;
	source->SetBuffer(ptr->m_soundBuffers->GetSoundBuffer("Data/Sounds/batman.wav"));

	ptr->m_soundManager->Play(source);

	return nullptr;
}

void* m_selectFunc(void* packet)
{
	GameScreen* ptr = (GameScreen*)packet;
	Vector mousepos = ptr->m_input->GetMousePos();
	mousepos.x -= ptr->m_guiparams.LevelEditorTableX;
	mousepos.y -= ptr->m_guiparams.LevelEditorTableY;
	int sx, sy;
	sx = int(mousepos.x / ptr->m_guiparams.LevelEditorCellX);
	sy = int(mousepos.y / ptr->m_guiparams.LevelEditorCellY)* ptr->m_guiparams.LevelEditorCellColumn;
	ptr->m_selectedItem = sx + sy;
	ptr->m_selectedObject = nullptr;
	return nullptr;
}