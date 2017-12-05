#pragma once
#include <Engine\Application.hpp>
#include <Engine\ResourceManager.hpp>
#include <Engine\Camera.hpp>
#include <Engine\Font.hpp>
#include <Engine\Config.hpp>
#include <Engine\Timer.hpp>
#include <Engine\GUI.hpp>
#include "LevelReader.hpp"
#include <Engine/Npc.hpp>
#include <Engine/AnimationFactory.hpp>
#include <Engine/ObjectFactory.hpp>

#include "GUIClasses.hpp"
#include "GameScreenGUI.hpp"


using namespace ThrashEngine;


class GameScreen :public ThrashEngine::Application
{
public:
	GameScreen();
	~GameScreen();

	virtual ResultState Draw() override;
	virtual ResultState Update() override;
	virtual ResultState OnInit()override;
	virtual ResultState OnShutdown()override;
	virtual ResultState DrawGUIText();

	void AddObject(std::string name, double x, double y, double w,double h,bool stat);
	void AddAnimaton(NPC*);
public:
	TextureManager* m_textures;
	SoundBufferManager* m_soundBuffers;
	Font* m_font;
	Text m_monitorField;
	Text m_playerstats_text;
	Text m_testtext;
	ObjectManager* m_world;
	Camera* m_camera;
	NPC* m_player;

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

	GUIInputLabel m_inputlabel;

	SoundSource* m_music;
	SoundManager* m_soundManager;

	GUIDeveloperConsole m_console;

	ObjectFactory* m_objectFactory;
	AnimationObjectFactory* m_animobjectFactory;
	NpcFactory* m_npcFactory;
	AnimationFactory* m_animFactory;

	//---------Level Editor variables----------//
	bool m_levelEditorState;
	int m_selectedItem;
	Object* m_selectedObject;

	Object** LevelEditorSelectorItems;
	GUIButton* LevelEditorSelectorButtons;
	Text m_nameField;

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

	struct GuiParam
	{
		 int GameWindowWidth ;
		 int GameWindowHeight ;

		 int LevelEditorTableX ;
		 int LevelEditorTableY;

		 int LevelEditorCellX ;
		 int LevelEditorCellY ;

		 int LevelEditorCellColumn ;
		 int LevelEditorCellRow ;

		 int LevelEditorParamX ;
		 int LevelEditorParamY;

		 int EditorMouseScroll;
		 int EditorMouseBorderScroll;

		 double ScalingWidth;
		 double ScalingHeight ;
	} m_guiparams;

};

