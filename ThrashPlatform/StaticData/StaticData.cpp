#pragma once
#include "StaticData.hpp"
static int CreateNpcFactory(NpcFactory* factory, GameScreen* screen)
{
	//Create Player
	NPC* player = new NPC();
	player->m_collideable = true;
	player->m_debug = true;
	player->m_active = true;
	player->m_static = false;
	player->m_pos.w = 46;
	player->m_pos.h = 50;
	//player->.x = 46;
	player->m_animUV = ThrashEngine::Rectangle(46, 50,8,8);
	player->SetTexture(screen->m_textures->GetTexture("Data/Sprites/playerSprite.bmp"));
	player->SetAnimation(screen->m_animFactory->GetAnimationInstance("Player"),"Player");
	factory->AddNewNpc("Player", player);

	//Create enemy
	NPC* enemy = new NPC();
	//*enemy = *player;	
	enemy->m_collideable = true;
	enemy->m_debug = true;
	enemy->m_active = true;
	enemy->m_static = false;
	enemy->m_pos.w = 64;
	enemy->m_pos.h = 64;
	enemy->SetTexture(screen->m_textures->GetTexture("Data/Sprites/player.bmp"));
	factory->AddNewNpc("Marine", enemy);

	player->m_property->Set("CanJump", 0);

	return 1;
}

static int CreateObjectFactory(ObjectFactory* factory, GameScreen* screen)
{
	Object* woodPlatform = new Object();
	woodPlatform->m_active = true;
	woodPlatform->m_collideable = true;
	woodPlatform->m_debug = true;
	woodPlatform->m_static = true;
	woodPlatform->SetTexture(screen->m_textures->GetTexture("Data/Sprites/wood64.bmp"));
	factory->AddNewObject("WoodPlatform", woodPlatform);

	Object* grassPlatform = new Object(*woodPlatform);
	woodPlatform->SetTexture(screen->m_textures->GetTexture("Data/Sprites/grass.bmp"));
	factory->AddNewObject("GrassPlatform", grassPlatform);
	return 1;
}

static int CreateAnimations(ThrashEngine::AnimationFactory* factory, GameScreen* screen)
{

	factory->AddAnimation("PlayerMoveRight",24,30,5);
	factory->AddAnimation("PlayerMoveLeft", 56, 63, 5);
	factory->AddAnimation("PlayerStandRight", 0, 0, 100000);
	factory->AddAnimation("PlayerStandLeft", 39, 39, 100000);
	factory->AddAnimation("PlayerJumpRight", 6, 6, 0);
	factory->AddAnimation("PlayerJumpLeft", 33, 33, 0);
	factory->AddAnimation("PlayerFallRight", 7, 7, 0);
	factory->AddAnimation("PlayerFallLeft", 32, 32, 0);

	factory->CreateInstance("Player");

	factory->AddAnimationToInstance("Player", "PlayerMoveRight");
	factory->AddAnimationToInstance("Player", "PlayerMoveLeft");
	factory->AddAnimationToInstance("Player", "PlayerStandRight");
	factory->AddAnimationToInstance("Player", "PlayerStandLeft");
	factory->AddAnimationToInstance("Player", "PlayerJumpRight");
	factory->AddAnimationToInstance("Player", "PlayerJumpLeft");
	factory->AddAnimationToInstance("Player", "PlayerFallRight");
	factory->AddAnimationToInstance("Player", "PlayerFallLeft");



	return 1;
}

static int CreateGameSystem(GameScreen* screen)
{
	//Create Graphics
	screen->m_textures = new ThrashEngine::TextureManager(screen->m_graphics);
	screen->m_textures->SetColorKey(screen->m_graphics->GetColor(255, 255, 255));
	//Create Sound
	screen->m_soundBuffers = new ThrashEngine::SoundBufferManager();
	screen->m_soundManager = new ThrashEngine::SoundManager();
	//Create World
	screen->m_world = new ThrashEngine::ObjectManager;
	screen->m_world->m_property.Set("CollisionUpdateTime", 60);
	//Create Animations Factory
	screen->m_animFactory = new ThrashEngine::AnimationFactory;

	//Create Object Factories
	screen->m_objectFactory = new ObjectFactory;
	screen->m_animobjectFactory = new AnimationObjectFactory;
	screen->m_npcFactory = new NpcFactory;

	//Create Font
	screen->m_font = new ThrashEngine::Font;
	screen->m_font->LoadFont("Data/font.ttf", 32);
	return 1;
}


static int CreateInitGamesStaticData(GameScreen* screen)
{
	//Create animations
	CreateAnimations(screen->m_animFactory, screen);

	CreateObjectFactory(screen->m_objectFactory, screen);
	CreateNpcFactory(screen->m_npcFactory, screen);

	return 1;
}

static int LoadConfigs(GameScreen* screen, std::string configPath)
{

	screen->m_guiparams.GameWindowWidth = 1024;
	screen->m_guiparams.GameWindowHeight = 768;

	screen->m_guiparams.LevelEditorTableX = 100;
	screen->m_guiparams.LevelEditorTableY = 600;

	screen->m_guiparams.LevelEditorCellX = 32;
	screen->m_guiparams.LevelEditorCellY = 32;

	screen->m_guiparams.LevelEditorCellColumn = 10;
	screen->m_guiparams.LevelEditorCellRow = 2;

	screen->m_guiparams.LevelEditorParamX = screen->m_guiparams.LevelEditorTableX + screen->m_guiparams.LevelEditorCellX*(screen->m_guiparams.LevelEditorCellColumn);
	screen->m_guiparams.LevelEditorParamY = 400;

	screen->m_guiparams.EditorMouseScroll = 5;
	screen->m_guiparams.EditorMouseBorderScroll = 10;

	screen->m_guiparams.ScalingWidth = 1.0;
	screen->m_guiparams.ScalingHeight = 1.0;

	ThrashEngine::Config m_configFile;
	std::cout << "Loading " << configPath<< std::endl;
	if (!m_configFile.LoadConfig(configPath))
	{
		std::cout << "Failed to load config file" << std::endl;

		screen->m_slowdownVel = 0.1;
		screen->m_acceleration = 0.2;
		screen->m_playerMaxSpeed = 4.0;
		screen->m_gravity = 9.1 / 60;
		screen->m_playerMaxYSpeed = 9.1;
		screen->m_jumpVel = 5.0;
	}
	else {
		m_configFile.SetGroup("Game");
		ThrashEngine::ConfigData SlowDown = m_configFile.GetParam("SlowDownSpeed");
		ThrashEngine::ConfigData JumpSpeed = m_configFile.GetParam("JumpSpeed");
		ThrashEngine::ConfigData Gravity = m_configFile.GetParam("Gravity");
		ThrashEngine::ConfigData Accel = m_configFile.GetParam("Acceleration");
		ThrashEngine::ConfigData SpeedX = m_configFile.GetParam("PlayerMaxSpeedX");
		ThrashEngine::ConfigData SpeedY = m_configFile.GetParam("PlayerMaxSpeedY");

		ThrashEngine::ConfigData EnemyRangeP = m_configFile.GetParam("EnemyRange");
		ThrashEngine::ConfigData EnemyInteractionRangeP = m_configFile.GetParam("EnemyInteractionRange");
		ThrashEngine::ConfigData EnemyMaxSpeedP = m_configFile.GetParam("EnemyMaxSpeed");
		ThrashEngine::ConfigData EnemyAccelerationP = m_configFile.GetParam("EnemyAcceleration");
		ThrashEngine::ConfigData EnemyBreakSpeedP = m_configFile.GetParam("EnemyBreakSpeed");
		ThrashEngine::ConfigData EnemyMaxHPP = m_configFile.GetParam("EnemyMaxHP");
		ThrashEngine::ConfigData EnemyHPP = m_configFile.GetParam("EnemyHP");
		ThrashEngine::ConfigData EnemyDamageP = m_configFile.GetParam("EnemyDamage");
		ThrashEngine::ConfigData EnemyArmorP = m_configFile.GetParam("EnemyArmor");
		ThrashEngine::ConfigData EnemyInteractionColdDownP = m_configFile.GetParam("EnemyInteractionColdDown");

		m_configFile.SetGroup("Window");
		ThrashEngine::ConfigData ScreenX = m_configFile.GetParam("ScreenWidth");
		ThrashEngine::ConfigData ScreenY = m_configFile.GetParam("ScreenHeight");
		m_configFile.SetGroup("Editor");
		ThrashEngine::ConfigData EditorItemPickerX = m_configFile.GetParam("EditorItemPickerX");
		ThrashEngine::ConfigData EditorItemPickerY = m_configFile.GetParam("EditorItemPickerY");
		ThrashEngine::ConfigData EditorItemPickerCellX = m_configFile.GetParam("EditorItemPickerCellX");
		ThrashEngine::ConfigData EditorItemPickerCellY = m_configFile.GetParam("EditorItemPickerCellY");
		ThrashEngine::ConfigData EditorItemPickerColumn = m_configFile.GetParam("EditorItemPickerColumn");
		ThrashEngine::ConfigData EditorItemPickerRow = m_configFile.GetParam("EditorItemPickerRow");
		ThrashEngine::ConfigData EditorMouseScrollP = m_configFile.GetParam("EditorMouseScroll");
		ThrashEngine::ConfigData EditorMouseBorderScrollP = m_configFile.GetParam("EditorMouseBorderScroll");

		screen->m_slowdownVel = SlowDown.data;
		screen->m_acceleration = Accel.data;
		screen->m_playerMaxSpeed = SpeedX.data;
		screen->m_gravity = Gravity.data / 60;
		screen->m_playerMaxYSpeed = SpeedY.data;
		screen->m_jumpVel = JumpSpeed.data;

		screen->m_guiparams.LevelEditorTableX = EditorItemPickerX.data;
		screen->m_guiparams.LevelEditorTableY = EditorItemPickerY.data;
		screen->m_guiparams.LevelEditorCellX = EditorItemPickerCellX.data;
		screen->m_guiparams.LevelEditorCellY = EditorItemPickerCellY.data;
		screen->m_guiparams.LevelEditorCellColumn = EditorItemPickerColumn.data;
		screen->m_guiparams.LevelEditorCellRow = EditorItemPickerRow.data;
		screen->m_guiparams.EditorMouseScroll = EditorMouseScrollP.data;
		screen->m_guiparams.EditorMouseBorderScroll = EditorMouseBorderScrollP.data;
		screen->m_guiparams.LevelEditorParamX = screen->m_guiparams.LevelEditorTableX + screen->m_guiparams.LevelEditorCellX*(screen->m_guiparams.LevelEditorCellColumn);



		screen->EnemyRange = EnemyRangeP.data;
		screen->EnemyInteractionRange = EnemyInteractionRangeP.data;
		screen->EnemyMaxSpeed = EnemyMaxSpeedP.data;
		screen->EnemyAcceleration = EnemyAccelerationP.data;
		screen->EnemyBreakSpeed = EnemyBreakSpeedP.data;
		screen->EnemyMaxHP = EnemyMaxHPP.data;
		screen->EnemyHP = EnemyHPP.data;
		screen->EnemyDamage = EnemyDamageP.data;
		screen->EnemyArmor = EnemyArmorP.data;
		screen->EnemyInteractionColdDown = EnemyInteractionColdDownP.data;



		screen->m_window->ResizeWindow(ScreenX.data, ScreenY.data);

		//Set renderer scale
		screen->m_graphics->SetRendererScale(ScreenX.data / screen->m_guiparams.GameWindowWidth, ScreenY.data / screen->m_guiparams.GameWindowHeight);

	}
	return 1;
}

static int CreateGameGUI(GameScreen* screen)
{

	SDL_Color col;
	col.r = 0;
	col.g = 255;
	col.b = 255;
	col.a = 255;

	screen->m_gui.SetInput(screen->m_input);

	screen->m_monitorField.SetFont(screen->m_font);
	screen->m_monitorField.SetGraphics(screen->m_graphics);
	screen->m_monitorField.SetPos(ThrashEngine::Vector(0, 80));
	screen->m_monitorField.SetColor(Color(128, 128, 128));

	screen->m_testtext.SetFont(screen->m_font);
	screen->m_testtext.SetGraphics(screen->m_graphics);
	screen->m_testtext.SetPos(ThrashEngine::Vector(0, 200));
	screen->m_testtext.SetColor(col);

	screen->m_nameField.SetFont(screen->m_font);
	screen->m_nameField.SetGraphics(screen->m_graphics);
	screen->m_nameField.SetPos(ThrashEngine::Vector(800, 200));
	screen->m_nameField.SetColor(col);

	screen->m_playerstats_text.SetFont(screen->m_font);
	screen->m_playerstats_text.SetGraphics(screen->m_graphics);
	screen->m_playerstats_text.SetPos(ThrashEngine::Vector(0, 0));
	screen->m_playerstats_text.SetColor(Color(255, 255, 255));
	screen->m_playerstats_text.SetLetterSize(8, 16);

	screen->m_console.m_pos = Vector(0, 0);
	screen->m_console.SetSize(screen->m_guiparams.GameWindowWidth, 120);
	screen->m_console.SetFont(screen->m_font);
	screen->m_console.SetTextSize(12, 18);
	screen->m_console.SetBackgroundColorInfo(ThrashEngine::Color(40, 40, 40));
	screen->m_console.SetBorderColorInfo(ThrashEngine::Color(80, 80, 80));
	screen->m_console.SetBackgroundColor(ThrashEngine::Color(40, 40, 40));
	screen->m_console.SetBorderColor(ThrashEngine::Color(40, 40, 40));
	screen->m_console.SetHistorySizeView(10);
	screen->m_console.SetHistorySize(50);
	screen->m_console.m_debug = true;
	screen->m_gui.AddGUIObject(&screen->m_console);
	screen->m_gui.AddGUIObject(&screen->m_console.m_inputlabel);
	screen->m_console.SetActiveLabel(false);
	screen->m_console.m_inputlabel.SetInput(screen->m_input);
	screen->m_console.SetInput(screen->m_input);

	screen->m_gui.SetGraphics(screen->m_graphics);
	screen->m_gui.SetInput(screen->m_input);
	screen->m_exitButton.SetTexture(screen->m_textures->GetTexture("Data/Sprites/exitbut.bmp"));
	screen->m_exitButton.m_pos = Vector(0, 768 - 32);
	screen->m_exitButton.SetSize(64, 32);
	screen->m_exitButton.SetFunction(&m_exitFunc);
	screen->m_exitButton.m_debug = (false);
	screen->m_gui.AddGUIObject(&screen->m_exitButton);
	screen->m_exitButton.SetData((void*)screen);

	screen->m_saveButton.SetTexture(screen->m_textures->GetTexture("Data/Sprites/savebut.bmp"));
	screen->m_saveButton.m_pos = Vector(0, 768 - 96);
	screen->m_saveButton.SetSize(64, 32);
	screen->m_saveButton.SetFunction(&m_saveFunc);
	screen->m_saveButton.m_debug = (false);
	screen->m_gui.AddGUIObject(&screen->m_saveButton);
	screen->m_saveButton.SetData((void*)screen);
	screen->m_saveButton.m_active = (false);

	screen->m_openButton.SetTexture(screen->m_textures->GetTexture("Data/Sprites/loadbut.bmp"));
	screen->m_openButton.m_pos = Vector(0, 768 - 96);
	screen->m_openButton.SetSize(64, 32);
	screen->m_openButton.SetFunction(&m_openFunc);
	screen->m_openButton.m_debug = (false);
	screen->m_gui.AddGUIObject(&screen->m_openButton);
	screen->m_openButton.SetData((void*)screen);

	screen->m_editorButton.SetTexture(screen->m_textures->GetTexture("Data/Sprites/editbut.bmp"));
	screen->m_editorButton.m_pos = Vector(0, 768 - 64);
	screen->m_editorButton.SetSize(64, 32);
	screen->m_editorButton.SetFunction(&m_editFunc);
	screen->m_editorButton.m_debug = (false);
	screen->m_gui.AddGUIObject(&screen->m_editorButton);
	screen->m_editorButton.SetData((void*)screen);

	screen->m_inputlabel.m_pos = Vector(400, 400);
	screen->m_inputlabel.SetSize(200, 16);
	screen->m_inputlabel.m_debug = (true);
	screen->m_inputlabel.SetFont(screen->m_font);
	screen->m_gui.AddGUIObject(&screen->m_inputlabel);
	screen->m_inputlabel.SetBorderColor(Color(70, 70, 70));
	screen->m_inputlabel.SetBackgroundColor(Color(30, 30, 30));
	screen->m_inputlabel.SetTextSize(10, 16);
	return 1;
}