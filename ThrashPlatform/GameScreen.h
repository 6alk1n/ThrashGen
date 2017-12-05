#pragma once
#include <Engine\Application.hpp>
#include <Engine\ResourceManager.hpp>
#include <Engine\TileMap.hpp>
#include <Engine\Camera.hpp>
#include <Engine\Font.hpp>
#include <Engine\Config.hpp>
#include <Engine\Timer.hpp>
#include <Engine\GUI.hpp>
#include "LevelReader.hpp"
#include <Engine/Npc.hpp>

#include "GUIClasses.hpp"


const int GameWindowWidth = 1024;
const int GameWindowHeight = 768;

static int LevelEditorTableX = 100;
static int LevelEditorTableY = 600;

static int LevelEditorCellX = 64;
static int LevelEditorCellY = 64;

static int LevelEditorCellColumn = 10;
static int LevelEditorCellRow = 2;

static int LevelEditorParamX = LevelEditorTableX + LevelEditorCellX*LevelEditorCellColumn + 1;
static int LevelEditorParamY = 200;

static int EditorMouseScroll = 5;
static int EditorMouseBorderScroll = 10;

using namespace ThrashEngine;

void* m_exitFunc(void*);
void* m_saveFunc(void*);
void* m_openFunc(void*);
void* m_editFunc(void*);
void* m_selectFunc(void*);

class GameScreen :public ThrashEngine::Application
{
public:
	GameScreen();
	~GameScreen();

	virtual ResultState Draw() override;
	virtual ResultState Update() override;
	virtual ResultState OnInit()override;
	virtual ResultState OnShutdown()override;

	void AddObject(std::string name, double x, double y, double w,double h,bool stat);
	void AddAnimaton(NPC*);
public:
	TextureManager* m_textures;
	SoundBufferManager* m_soundBuffers;
	Font* m_font;
	FontField m_fontfield1;
	FontField m_fontfield2;
	FontField m_fontfield3;
	FontField m_fontfield4;
	FontField m_fontfield5;
	FontField m_monitorField1;
	TileMap* m_world;
	Camera* m_camera;
	NPC* m_player;
	bool m_canJump;
	Vector m_oldplayerpos;
	double m_slowdownVel;
	double m_playerMaxSpeed;
	double m_acceleration;
	double m_gravity;
	double m_jumpVel;
	double m_playerMaxYSpeed;
	Config* m_configFile;
	LevelReader m_levelreader;
	Timer m_timer;
	Timer m_supertim;
	double m_avgfps;
	NPC* m_enemy;
	ThrashEngine::GUI m_gui;
	GUIButton m_exitButton;
	GUIButton m_saveButton;
	GUIButton m_openButton;
	GUIButton m_editorButton;

	SoundSource* m_music;
	SoundManager* m_soundManager;


	//---------Level Editor variables----------//
	bool m_levelEditorState;
	int m_selectedItem;
	Object* m_selectedObject;

	Object** LevelEditorSelectorItems;
	GUIButton* LevelEditorSelectorButtons;
	FontField m_nameField;

	GUISpinButton m_SpinButtonWidth;
	GUISpinButton m_SpinButtonHeight;

	double EnemyRange;
	double EnemyInteractionRange;
	double EnemyMaxSpeed;
	double EnemyAcceleration;
	double EnemyBreakSpeed;
	double EnemyMaxHP;
	double EnemyHP;
	double EnemyDamage;
	double EnemyArmor;
	double EnemyInteractionColdDown;

};

