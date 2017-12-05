#include "GameScreen.h"
#include <Engine/Utility.hpp>
#include <Engine/Physics.hpp>
using namespace ThrashEngine;

GameScreen::GameScreen():Application()
{
}


GameScreen::~GameScreen()
{

}


ThrashEngine::ResultState GameScreen::Draw()
{
	m_world->Draw(m_graphics);
	for (auto i = m_world->m_collisions.begin(); i != m_world->m_collisions.end(); i++)
	{
		if (i->obj1 == m_player)
		{
			m_graphics->SetColor(255, 0, 0, 255);
			m_graphics->DrawRectOut(i->obj2->GetX() - m_camera->GetPos().x, i->obj2->GetY() - m_camera->GetPos().y, i->obj2->GetWidth(), i->obj2->GetHeight());
		}
	}
	m_fontfield1.ClearField();
	//m_fontfield1 << "Player position [" << m_player->GetX() << " : " << m_player->GetY() << "]" << "\n";
	m_fontfield1 << "Mouse delta [" << m_input->GetDeltaX() << " : " << m_input->GetDeltaY() << "]" << "\n";
	m_fontfield1 << "Object count: " << m_world->GetObjectCount();
	m_fontfield1 << " Collisions: " << m_world->m_collisions.size();
	m_fontfield1.Render();
	m_fontfield2.ClearField();
	m_fontfield2 << "Player velocity [" << m_player->GetVel().x << " : " << m_player->GetVel().y << "]  ";
//	m_fontfield2 << "Player Max Speed [" << m_playerMaxSpeed << " : " << m_playerMaxYSpeed << " ]";
	m_fontfield2 << "Sounds player:" << m_soundManager->GetSounds()->size();
	m_fontfield2.Render();
	m_fontfield3.ClearField();
	m_fontfield3 << "SlowDownSpeed : " << m_slowdownVel;
	m_fontfield3 << " Jump Velocity : " << m_jumpVel;
	m_fontfield3 << " Gravity Y: " << m_gravity;
	m_fontfield3 << " CanJump? ";
	if (m_canJump) m_fontfield3 << "Yes";
	else m_fontfield3 << "No";
	m_fontfield3 << " FPS: " << m_avgfps;
	m_fontfield3.Render();
	m_fontfield4.ClearField();
	m_fontfield4 << "Left/Right arrow keys to move. Space to jump. r - reset position. t - reset velocity.";
	m_fontfield4.Render();

	m_monitorField1.ClearField();
	double totaltime = m_monitor.GetMonitor("Toogle").diffTime * 1000;
	double drawtime = m_monitor.GetMonitor("DrawingFrame").diffTime * 1000;
	double updatetime = m_monitor.GetMonitor("UpdatingFrame").diffTime * 1000;

	m_monitorField1 << "Total: " <<totaltime <<
		" ms| DrawingFrame: " << drawtime << " ms, "<<(drawtime/totaltime) *100 <<"%"<<
		"| UpdatingFrame: " << updatetime<<" ms, " << (updatetime / totaltime) * 100 << "%";
	m_monitorField1.Render();

	if (m_player->properties.hp < 0)
	{
		m_fontfield5.ClearField();
		m_fontfield5 << "YOU DIED!!!";
		m_fontfield5.Render();
	}	

	if (m_levelEditorState)
	{
		m_graphics->SetColor(255, 0, 0, 255);
		SDL_Rect pos,uv;
		//Selector
		for (int n=0;n<LevelEditorCellRow;n++)
		for (int i = 0; i < LevelEditorCellColumn; i++)
		{
			m_graphics->DrawRectOut(LevelEditorTableX+i*LevelEditorCellX, LevelEditorTableY+n*LevelEditorCellY, LevelEditorCellX, LevelEditorCellY);
			if (LevelEditorSelectorItems[n*LevelEditorCellColumn + i]) {
				LevelEditorSelectorItems[n*LevelEditorCellColumn + i]->GetUV(uv.x, uv.y, uv.w, uv.h);
				pos.x = LevelEditorTableX + i*LevelEditorCellX;
				pos.y = LevelEditorTableY + n*LevelEditorCellY;
				pos.w = LevelEditorCellX;
				pos.h = LevelEditorCellY;
				if (LevelEditorSelectorItems[n*LevelEditorCellColumn + i]->GetTexture()) m_graphics->DrawTexture(LevelEditorSelectorItems[n*LevelEditorCellColumn + i]->GetTexture(), &pos, &uv);
			}
		}
		//Parametors
		m_graphics->SetColor(128, 128, 128,255);
		m_graphics->DrawRectXY(LevelEditorTableX + LevelEditorCellColumn*LevelEditorCellX+1, 200, m_window->GetScreenWidth(), m_window->GetScreenHeight());
		
		ThrashEngine::Object* selected;
		if (m_selectedItem != -1 && LevelEditorSelectorItems[m_selectedItem]) {
			selected = LevelEditorSelectorItems[m_selectedItem];
		}
		else
		{
			selected = m_selectedObject;
		}

		if (selected != nullptr)
		{
			pos.x = (LevelEditorParamX + m_window->GetScreenWidth())/2 - 32;
			pos.y = LevelEditorParamY + 32;
			pos.w = 64;
			pos.h = 64;

			selected->GetUV(uv.x, uv.y, uv.w, uv.h);

			m_graphics->DrawTexture(selected->GetTexture(), &pos, &uv);
			m_nameField.ClearField();
			m_nameField << selected->GetName();
			m_nameField.Render();
			
			Vector mousepos = m_input->GetMousePos();
			pos.x = mousepos.x;
			pos.y = mousepos.y;
			pos.w = m_SpinButtonWidth.GetValue();
			pos.h = m_SpinButtonHeight.GetValue();
			if (selected!=m_selectedObject)
			m_graphics->DrawTexture(selected->GetTexture(), &pos, &uv);

			m_SpinButtonWidth.SetActive(true);
			m_SpinButtonHeight.SetActive(true);
		}
		else
		{

			m_SpinButtonWidth.SetActive(false);
			m_SpinButtonHeight.SetActive(false);
		}

	}
	m_gui.Draw();
	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::Update()
{

	static unsigned int m_avgt = 0;
	static unsigned int m_avgc = 0;

	unsigned int controlled=0;
	static unsigned int moveside = 1;

	m_avgt+=m_monitor.GetMonitor("Toogle").diffTime;
	if (m_input->IsPressed(SDLK_RIGHT))
	{
		m_player->AddVelocity(Vector(m_acceleration, 0));
 		m_player->SetAnimation("MoveRight");
		controlled++;
		moveside = 1;
	}
	if (m_input->IsPressed(SDLK_LEFT))
	{
		m_player->AddVelocity(Vector(-m_acceleration, 0));
		m_player->SetAnimation("MoveLeft");
		controlled++;
		moveside = -1;
	}

	if (*(bool*)(m_player->GetProperty("CanJump").data)) {
		if (m_input->IsPressed(SDLK_SPACE))
		{
			m_player->AddVelocity(Vector(0, -m_jumpVel));
			m_player->SetProperty("CanJump", false);
			controlled++;
		}
	}
	if (!controlled)
	{
		if(moveside==1)m_player->SetAnimation("StandRight");
		else if(moveside==-1)m_player->SetAnimation("StandLeft");
	}
	if (m_player->GetVel().y > 0)
	{
		if (moveside == 1)m_player->SetAnimation("FallRight");
		if (moveside == -1)m_player->SetAnimation("FallLeft");
	}
	else if (m_player->GetVel().y < 0)
	{
		if (moveside == 1)m_player->SetAnimation("JumpRight");
		if (moveside == -1)m_player->SetAnimation("JumpLeft");
	}
	if (m_input->IsPressed(SDLK_r))
	{
		m_player->SetPos(50, 50);
	}
	if (m_input->IsPressed(SDLK_t))
	{
		m_player->SetVel(0, 0);
	}

	//Camera scrolling and interacting
	if (m_levelEditorState)
	{
		Vector mousepos = m_input->GetMousePos();
		if (mousepos.x < EditorMouseBorderScroll) m_camera->Move(Vector(-EditorMouseScroll, 0));
		else if (mousepos.x >m_window->GetScreenWidth()-10) m_camera->Move(Vector(EditorMouseScroll, 0));
		if (mousepos.y < EditorMouseBorderScroll) m_camera->Move(Vector(0, -EditorMouseScroll));
		else if (mousepos.y >m_window->GetScreenHeight() - 10) m_camera->Move(Vector(0, EditorMouseScroll));

		if (m_input->OnDown(MOUSE_LEFT))
		{
			ThrashEngine::Rectangle rectParam (LevelEditorParamX,LevelEditorParamY,m_window->GetScreenWidth(),m_window->GetScreenHeight());
			ThrashEngine::Rectangle rectList(LevelEditorTableX, LevelEditorTableY, LevelEditorTableX + LevelEditorCellX*LevelEditorCellColumn, LevelEditorTableY + LevelEditorCellY*LevelEditorCellRow);
			ThrashEngine::Rectangle rectButton(0, 768 - 96, 64, 96);
			if (!isPointinRect(mousepos, rectParam) && !isPointinRect(mousepos, rectList) && !isPointinRect(mousepos, rectButton))
			{
				if (m_selectedItem>0 && m_selectedItem<LevelEditorCellColumn*LevelEditorCellRow) {

					if (LevelEditorSelectorItems[m_selectedItem]->GetVirtualState() == VirtualStateObject) //is object
					{
						ThrashEngine::Object* obj = m_world->CreateObject(LevelEditorSelectorItems[m_selectedItem]->GetName());
						obj->SetActive(true);
						obj->SetDebugDraw(true);
						obj->SetSize(m_SpinButtonWidth.GetValue(), m_SpinButtonHeight.GetValue());
						obj->SetPos(mousepos+m_camera->GetPos());
					}
					else
					{
						if (LevelEditorSelectorItems[m_selectedItem]->GetVirtualState() == VirtualStateNPC)
						{
							NPC* newenemy = CreateNPC(LevelEditorSelectorItems[m_selectedItem]->GetName(), m_world);
							newenemy->SetPos(mousepos + m_camera->GetPos());
							newenemy->SetSize(m_SpinButtonWidth.GetValue(), m_SpinButtonHeight.GetValue());
							newenemy->properties.fraction = 2;
							newenemy->properties.range = EnemyRange;
							newenemy->properties.InteractionRange = EnemyInteractionRange;
							newenemy->properties.MaxSpeed = EnemyMaxSpeed;
							newenemy->properties.Acceleration = EnemyAcceleration;
							newenemy->properties.breakSpeed = EnemyBreakSpeed;
							newenemy->properties.maxhp = EnemyMaxHP;
							newenemy->properties.hp = EnemyHP;
							newenemy->properties.damage = EnemyDamage;
							newenemy->properties.armor = EnemyArmor;
							newenemy->properties.interactionColdDown = EnemyInteractionColdDown;
							newenemy->canJump = true;
							newenemy->EnableAI(true);
						}
					}
				}
				else
				{
					for (auto i = m_world->GetSpritePtr()->begin(); i != m_world->GetSpritePtr()->end(); i++)
					{
						if (isPointinRect(mousepos + m_camera->GetPos(), i[0]->GetRect()))
						{
							m_selectedObject = (Object*)(i[0]);
							m_SpinButtonWidth.SetValue(m_selectedObject->GetWidth());
							m_SpinButtonHeight.SetValue(m_selectedObject->GetHeight());
							break;
						}
					}
				}
			}
		}
		if (m_input->IsPressed(MOUSE_LEFT) && m_selectedObject)
		{
			if (isPointinRect(mousepos + m_camera->GetPos(), m_selectedObject->GetRect()))
			{
				m_selectedObject->Move(m_input->GetDeltaX(),m_input->GetDeltaY());
			}
		}
		if (m_selectedObject) {
			m_selectedObject->SetSize(m_SpinButtonWidth.GetValue(), m_SpinButtonHeight.GetValue());
		}
	}

	if (!m_levelEditorState)
	m_camera->Center(m_player->GetPos());
	m_oldplayerpos = m_player->GetPos();
	m_player->AddVelocity(0.0, (m_gravity)); //gravity
	if (abs(m_player->GetVel().x)> m_playerMaxSpeed)
	{
		if (m_player->GetVel().x>0) m_player->SetVelX(m_playerMaxSpeed);
		else m_player->SetVelX(-m_playerMaxSpeed);
	}
	if (abs(m_player->GetVel().y)> m_playerMaxYSpeed)
	{
		if (m_player->GetVel().y>0) m_player->SetVelY(m_playerMaxYSpeed);
		else m_player->SetVelY(-m_playerMaxYSpeed);
	}
	if(!m_levelEditorState)
	m_world->Update(1.0);

	/*if (abs(m_oldplayerpos.y - m_player->GetY() )<0.01) //Is standing on the ground (vertically didn't moved)
	{
		m_canJump = true;
	}*/
	
	if (abs(m_player->GetVel().x )<0.1) m_player->SetVelX(0.0);
	else if (m_player->GetVel().x>0) m_player->AddVelocity(-m_slowdownVel,0);
	else  m_player->AddVelocity(m_slowdownVel, 0);
	m_avgc++;
	if (m_avgt > 1000)
	{
		m_avgfps = m_avgt*m_avgc /1000;
		m_avgt = 0;
		m_avgc = 0;
	}
	m_gui.Update(1.0);
	m_soundManager->Update();
	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::OnInit()
{
	m_textures = new ThrashEngine::TextureManager(m_graphics);
	m_textures->SetColorKey(m_graphics->GetColor(255,255,255));
	m_soundBuffers = new ThrashEngine::SoundBufferManager();
	m_world = new ThrashEngine::TileMap;
	m_world->UpdateCollisionTimeSet(60);
	if (m_levelreader.LoadLevel(m_world, "Data/levelsave1.lvl", m_textures));
	else
	{
		std::cout << "Unable to load Data/levelsave1.lvl" << std::endl;
		m_levelreader.ReadHeader(m_world, "Data/ObjectTypes.txt", m_textures);
		m_levelreader.ReadHeader(m_world, "Data/ObjectTyped.txt", m_textures);
	}
	//m_levelreader.ReadHeader(m_world, "Data/ObjectTypes.txt", m_textures);
	//m_levelreader.ReadHeader(m_world, "Data/ObjectTyped.txt", m_textures);
	m_player = CreateNPC("Player", m_world);
	m_player->properties.armor = 0;
	m_player->properties.damage = 3;
	m_player->properties.maxhp = 50;
	m_player->properties.hp = 50;
	m_player->properties.interactionColdDown = 60;
	ThrashEngine::Animation anim;
	m_player->SetUVCell(46, 50);

	AddAnimaton(m_player);


	m_camera = new Camera;
	m_camera->SetView(Vector(1024, 768));
	m_canJump = false;
	m_player->SetPos(50, 50);
	m_world->SetCamera(m_camera);

	m_font = new ThrashEngine::Font;
	m_font->LoadFont("Data/font.ttf", 16);
	SDL_Color col;
	col.r = 0;
	col.g = 255;
	col.b = 255;
	col.a = 255;

	m_fontfield1.SetFont(m_font);
	m_fontfield1.SetGraphics(m_graphics);
	m_fontfield1.SetPos(ThrashEngine::Vector(0, 0));
	m_fontfield1.SetSize(ThrashEngine::Vector(800, 32));
	m_fontfield1.SetColor(col);

	m_fontfield2.SetFont(m_font);
	m_fontfield2.SetGraphics(m_graphics);
	m_fontfield2.SetPos(ThrashEngine::Vector(0, 32));
	m_fontfield2.SetSize(ThrashEngine::Vector(800, 32));
	m_fontfield2.SetColor(col);

	m_fontfield3.SetFont(m_font);
	m_fontfield3.SetGraphics(m_graphics);
	m_fontfield3.SetPos(ThrashEngine::Vector(0, 64));
	m_fontfield3.SetSize(ThrashEngine::Vector(800, 32));
	m_fontfield3.SetColor(col);
	col.r = 255;
	col.g = 0;
	col.b = 255;
	col.a = 255;
	m_fontfield4.SetFont(m_font);
	m_fontfield4.SetGraphics(m_graphics);
	m_fontfield4.SetPos(ThrashEngine::Vector(0, 96));
	m_fontfield4.SetSize(ThrashEngine::Vector(800, 32));
	m_fontfield4.SetColor(col);

	m_fontfield5.SetFont(m_font);
	m_fontfield5.SetGraphics(m_graphics);
	m_fontfield5.SetPos(ThrashEngine::Vector(0, 128));
	m_fontfield5.SetSize(ThrashEngine::Vector(800, 32));
	m_fontfield5.SetColor(col);

	col.r = 0;
	col.g = 255;
	col.b = 255;

	m_nameField.SetFont(m_font);
	m_nameField.SetGraphics(m_graphics);
	m_nameField.SetPos(ThrashEngine::Vector((LevelEditorParamX+m_window->GetScreenWidth())/2-64, LevelEditorParamY+100));
	m_nameField.SetSize(ThrashEngine::Vector(128, 32));
	m_nameField.SetColor(col);

	col.r = 255;
	col.g = 255;
	col.b = 255;

	m_monitorField1.SetFont(m_font);
	m_monitorField1.SetGraphics(m_graphics);
	m_monitorField1.SetPos(ThrashEngine::Vector(0,160));
	m_monitorField1.SetSize(ThrashEngine::Vector(800, 32));
	m_monitorField1.SetColor(col);

	ThrashEngine::Config m_configFile;
	std::cout << "Loading Data/config.cfg" << std::endl;
	if (!m_configFile.LoadConfig("Data/config.cfg"))
	{
		std::cout << "Failed to load config file" << std::endl;

		m_slowdownVel = 0.1;
		m_acceleration = 0.2;
		m_playerMaxSpeed = 4.0;
		m_gravity = 9.1 / 60;
		m_playerMaxYSpeed = 9.1;
		m_jumpVel = 5.0;
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

		m_slowdownVel = SlowDown.data;
		m_acceleration = Accel.data;
		m_playerMaxSpeed = SpeedX.data;
		m_gravity = Gravity.data / 60;
		m_playerMaxYSpeed = SpeedY.data;
		m_jumpVel = JumpSpeed.data;

		LevelEditorTableX = EditorItemPickerX.data;
		LevelEditorTableY = EditorItemPickerY.data;
		LevelEditorCellX = EditorItemPickerCellX.data;
		LevelEditorCellY = EditorItemPickerCellY.data;
		LevelEditorCellColumn = EditorItemPickerColumn.data;
		LevelEditorCellRow = EditorItemPickerRow.data;
		LevelEditorParamX = LevelEditorTableX + LevelEditorCellX*LevelEditorCellColumn + 1;
		EditorMouseScroll = EditorMouseScrollP.data;
		EditorMouseBorderScroll = EditorMouseBorderScrollP.data;

		EnemyRange = EnemyRangeP.data;
		EnemyInteractionRange= EnemyInteractionRangeP.data;
		EnemyMaxSpeed= EnemyMaxSpeedP.data;
		EnemyAcceleration= EnemyAccelerationP.data;
		EnemyBreakSpeed= EnemyBreakSpeedP.data;
		EnemyMaxHP= EnemyMaxHPP.data;
		EnemyHP= EnemyHPP.data;
		EnemyDamage= EnemyDamageP.data;
		EnemyArmor= EnemyArmorP.data;
		EnemyInteractionColdDown= EnemyInteractionColdDownP.data;
		


		m_window->ResizeWindow(ScreenX.data, ScreenY.data);

		//Set renderer scale
		m_graphics->SetRendererScale(ScreenX.data / GameWindowWidth, ScreenY.data/ GameWindowHeight);

	}
	//m_levelreader.SaveLevel(m_world, "Data/levelsave1.lvl");
	m_timer.Start();
	m_avgfps = 0;

	m_player->EnableAI(false);
	m_player->properties.fraction = 1;

//	m_enemy = (NPC*)m_world->CreateObject("PlayerSprite");
	
/*	m_enemy = CreateNPC("PlayerSprite", m_world);
	m_enemy->SetPos(500, 300);
	m_enemy->properties.fraction = 2;
	m_enemy->properties.range = 400;
	m_enemy->properties.InteractionRange = 50;
	m_enemy->properties.MaxSpeed = 7;
	m_enemy->properties.Acceleration = 5;
	m_enemy->properties.breakSpeed = 0.1;
	m_enemy->properties.maxhp = 10;
	m_enemy->properties.hp = 5;
	m_enemy->properties.damage = 1;
	m_enemy->properties.armor = 1;
	m_enemy->properties.interactionColdDown = 60;

	NPC* newenemy = CreateNPC("PlayerSprite", m_world);
	newenemy->SetPos(2100, 300);
	newenemy->properties.fraction = 2;
	newenemy->properties.range = 400;
	newenemy->properties.InteractionRange = 10;
	newenemy->properties.MaxSpeed = 9;
	newenemy->properties.Acceleration = 5;
	newenemy->properties.breakSpeed = 0.2;
	newenemy->properties.maxhp = 10;
	newenemy->properties.hp = 7;
	newenemy->properties.damage = 3;
	newenemy->properties.armor = 1;
	newenemy->properties.interactionColdDown = 30;

	newenemy = CreateNPC("PlayerSprite", m_world);
	newenemy->SetPos(1100, 500);
	newenemy->properties.fraction = 2;
	newenemy->properties.range = 700;
	newenemy->properties.InteractionRange = 50;
	newenemy->properties.MaxSpeed = 5;
	newenemy->properties.Acceleration = 2;
	newenemy->properties.breakSpeed = 0.15;
	newenemy->properties.maxhp = 20;
	newenemy->properties.hp = 5;
	newenemy->properties.damage = 1;
	newenemy->properties.armor = 2;
	newenemy->properties.interactionColdDown = 15;*/

//	m_levelreader.AddFreeSave(m_player);
//	m_levelreader.SaveLevel(m_world, "Data/levelsave1.lvl");

	m_gui.SetGraphics(m_graphics);
	m_gui.SetInput(m_input);
	m_exitButton.SetTexture(m_textures->GetTexture("Data/Sprites/exitbut.bmp"));
	m_exitButton.SetPos(0, 768 - 32);
	m_exitButton.SetSize(64, 32);
	m_exitButton.SetFunction(&m_exitFunc);
	m_exitButton.SetDebugDraw(false);
	m_gui.AddGUIObject(&m_exitButton);
	m_exitButton.SetData((void*)this);

	m_saveButton.SetTexture(m_textures->GetTexture("Data/Sprites/savebut.bmp"));
	m_saveButton.SetPos(0, 768 - 96);
	m_saveButton.SetSize(64, 32);
	m_saveButton.SetFunction(&m_saveFunc);
	m_saveButton.SetDebugDraw(false);
	m_gui.AddGUIObject(&m_saveButton);
	m_saveButton.SetData((void*)this);
	m_saveButton.SetActive(false);

	m_openButton.SetTexture(m_textures->GetTexture("Data/Sprites/loadbut.bmp"));
	m_openButton.SetPos(0, 768 - 96);
	m_openButton.SetSize(64, 32);
	m_openButton.SetFunction(&m_openFunc);
	m_openButton.SetDebugDraw(false);
	m_gui.AddGUIObject(&m_openButton);
	m_openButton.SetData((void*)this);	
	
	m_editorButton.SetTexture(m_textures->GetTexture("Data/Sprites/editbut.bmp"));
	m_editorButton.SetPos(0, 768 - 64);
	m_editorButton.SetSize(64, 32);
	m_editorButton.SetFunction(&m_editFunc);
	m_editorButton.SetDebugDraw(false);
	m_gui.AddGUIObject(&m_editorButton);
	m_editorButton.SetData((void*)this);

	//Level editor GUI stuff

	LevelEditorSelectorItems = new Object*[LevelEditorCellColumn*LevelEditorCellRow];
	for (int i = 0; i < LevelEditorCellColumn*LevelEditorCellRow; i++)
		LevelEditorSelectorItems[i] = nullptr;

	LevelEditorSelectorItems[2] = m_world->CreateObject("WoodPlatform");
	LevelEditorSelectorItems[2]->SetActive(false);	
	LevelEditorSelectorItems[2]->SetCollision(false);
	LevelEditorSelectorItems[2]->SetDebugDraw(false);
	LevelEditorSelectorItems[2]->SetPos(-1000,-1000);

	m_levelreader.AddFreeSave(LevelEditorSelectorItems[2]);

	LevelEditorSelectorItems[1] = m_world->CreateObject("GrassPlatform");
	LevelEditorSelectorItems[1]->SetActive(false);
	LevelEditorSelectorItems[1]->SetCollision(false);
	LevelEditorSelectorItems[1]->SetDebugDraw(false);
	LevelEditorSelectorItems[1]->SetPos(-1000, -1000);

	m_levelreader.AddFreeSave(LevelEditorSelectorItems[1]);

	LevelEditorSelectorItems[10] = CreateNPC("PlayerSprite",m_world);
	LevelEditorSelectorItems[10]->SetActive(false);
	LevelEditorSelectorItems[10]->SetCollision(false);
	LevelEditorSelectorItems[10]->SetDebugDraw(false);
	LevelEditorSelectorItems[10]->SetPos(-1000, -1000);

	m_levelreader.AddFreeSave(LevelEditorSelectorItems[10]);
	
	SDL_Color bordcol;
	bordcol.r = 255;
	bordcol.g = 255;
	bordcol.b = 0;
	bordcol.a = 255;
	LevelEditorSelectorButtons=new GUIButton[LevelEditorCellColumn*LevelEditorCellRow];
	for (int i = 0; i < LevelEditorCellColumn*LevelEditorCellRow; i++)
	{
		LevelEditorSelectorButtons[i].SetSize(LevelEditorCellX, LevelEditorCellY);
		LevelEditorSelectorButtons[i].SetFunction(&m_selectFunc);
		LevelEditorSelectorButtons[i].SetDebugDraw(false);
		m_gui.AddGUIObject(&(LevelEditorSelectorButtons[i]));
		LevelEditorSelectorButtons[i].SetData((void*)this);	
		LevelEditorSelectorButtons[i].SetPos(LevelEditorTableX+(i%LevelEditorCellColumn)*LevelEditorCellX, LevelEditorTableY + (i/LevelEditorCellColumn) *LevelEditorCellY);
		LevelEditorSelectorButtons[i].SetSize(LevelEditorCellX, LevelEditorCellY);
		LevelEditorSelectorButtons[i].SetBorderColor(bordcol);
		LevelEditorSelectorButtons[i].SetActive(false);
	}
	m_selectedItem = -1;

	m_SpinButtonWidth.SetFont(m_font);
	m_SpinButtonWidth.SetTexture(m_textures->GetTexture("Data/Sprites/spinbut-horizont.bmp"));
	m_SpinButtonWidth.SetPos(LevelEditorParamX+10 , LevelEditorParamY + 150);
	m_SpinButtonWidth.SetSize(120, 75);
	m_SpinButtonWidth.SetDebugDraw(false);
	m_gui.AddGUIObject(&m_SpinButtonWidth);
	m_SpinButtonWidth.SetMax(500);
	m_SpinButtonWidth.SetMin(10);
	m_SpinButtonWidth.SetValue(32);
	m_SpinButtonWidth.SetStep(1);
	m_SpinButtonWidth.SetTextSizeRelative(0.7);
	m_SpinButtonWidth.SetActive(false);
	m_SpinButtonWidth.SetText("width");

	m_SpinButtonHeight.SetFont(m_font);
	m_SpinButtonHeight.SetTexture(m_textures->GetTexture("Data/Sprites/spinbut-horizont.bmp"));
	m_SpinButtonHeight.SetPos(LevelEditorParamX + 140, LevelEditorParamY + 150);
	m_SpinButtonHeight.SetSize(120, 75);
	m_SpinButtonHeight.SetDebugDraw(false);
	m_gui.AddGUIObject(&m_SpinButtonHeight);
	m_SpinButtonHeight.SetMax(500);
	m_SpinButtonHeight.SetMin(10);
	m_SpinButtonHeight.SetValue(32);
	m_SpinButtonHeight.SetStep(1);
	m_SpinButtonHeight.SetTextSizeRelative(0.7);
	m_SpinButtonHeight.SetActive(false);
	m_SpinButtonHeight.SetText("height");

	m_soundManager = new SoundManager();

	m_selectedObject = nullptr;
	m_soundBuffers->GetSoundBuffer("Data/Sounds/batman.wav");
	
	m_music = new SoundSource();
	m_music->SetBuffer(m_soundBuffers->GetSoundBuffer("Data/Sounds/Tumburag.wav"));
	alSourcei(m_music->GetSource(), AL_LOOPING, AL_TRUE);
	m_soundManager->Play(m_music);
	m_player->canJump = true;
	m_player->SetVirtualState(VirtualStatePlayer);
	m_player->timeBetweenJump = 60;
	m_monitor.SetSubMonitorArray(60);
	m_player->SetProperty("CanJump", true);
	m_player->SetProperty("TimeBetweenJump", 90.0);
	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::OnShutdown()
{
	m_done = true;
	return ResultState::Success;
}

void GameScreen::AddObject(std::string name, double x, double y, double w=0, double h=0, bool stat=false)
{
	Object* obj = m_world->CreateObject(name);
	obj->SetPos(x, y);
	if( w && h) obj->SetSize(w, h);
	obj->m_static = stat;
}

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
	std::string file = ThrashEngine::Utility::DialogSaveFile("Save Level","Level Files\0 * .lvl\0", OFN_OVERWRITEPROMPT);

 	file += ".lvl";
	if (file.size()) {
		GameScreen* ptr = (GameScreen*)packet;
		ptr->m_levelreader.AddFreeSave(ptr->m_player);
		ptr->m_levelreader.SaveLevel(ptr->m_world, file);
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
		ptr->m_levelreader.LoadLevel(ptr->m_world, file,ptr-> m_textures);
		ptr->m_player = CreateNPC("Player", ptr->m_world);
		ptr->m_player->properties.armor = 0;
		ptr->m_player->properties.damage = 3;
		ptr->m_player->properties.maxhp = 50;
		ptr->m_player->properties.hp = 50;
		ptr->m_player->properties.interactionColdDown = 60;
		ptr->m_player->SetUVCell(46, 50);
		ptr->AddAnimaton(ptr->m_player);

		ptr->m_canJump = false;
		ptr->m_player->SetPos(50, 50); 
		ptr->m_player->EnableAI(false);
		ptr->m_player->properties.fraction = 1;
		ptr->m_player->canJump = true;
		ptr->m_player->SetVirtualState(VirtualStatePlayer);
		ptr->m_player->timeBetweenJump = 60;

		ptr->m_player->SetProperty("CanJump", true);

	}
	return nullptr;
}
void* m_editFunc(void* packet)
{
	GameScreen* ptr = (GameScreen*)packet;
	ptr->m_levelEditorState = !ptr->m_levelEditorState;
	if (ptr->m_levelEditorState)
	{
		ptr->m_saveButton.SetActive(true);
		ptr->m_openButton.SetActive(false);
		for (int i = 0; i < LevelEditorCellColumn*LevelEditorCellRow; i++)
			ptr->LevelEditorSelectorButtons[i].SetActive(true);
		ptr->m_SpinButtonWidth.SetActive(true);	
		ptr->m_SpinButtonHeight.SetActive(true);
	}
	else
	{
		ptr->m_saveButton.SetActive(false);
		ptr->m_openButton.SetActive(true);
		for (int i = 0; i < LevelEditorCellColumn*LevelEditorCellRow; i++)
			ptr->LevelEditorSelectorButtons[i].SetActive(false);	
		ptr->m_SpinButtonWidth.SetActive(false);
		ptr->m_SpinButtonHeight.SetActive(false);
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
	mousepos.x -= LevelEditorTableX;
	mousepos.y -= LevelEditorTableY;
	ptr->m_selectedItem = int (mousepos.x / LevelEditorCellX) + int (mousepos.y / LevelEditorCellY)* LevelEditorCellColumn;
	ptr->m_selectedObject = nullptr;
	return nullptr;
}
void GameScreen::AddAnimaton(NPC* npc)
{
	ThrashEngine::Animation anim;
	anim.animName = "MoveRight";
	anim.startAnim = 24;
	anim.endAnim = 30;
	anim.loop = true;
	anim.frameTime = 5;
	npc->AddAnimation(anim);	
	
	anim.animName = "MoveLeft";
	anim.startAnim = 56;
	anim.endAnim = 63;
	anim.loop = true;
	anim.frameTime = 5;
	npc->AddAnimation(anim);

	anim.animName = "StandRight";
	anim.startAnim = 0;
	anim.endAnim = 0;
	anim.loop = false;
	anim.frameTime = 100000;
	npc->AddAnimation(anim);

	anim.animName = "StandLeft";
	anim.startAnim = 39;
	anim.endAnim = 39;
	anim.loop = false;
	anim.frameTime = 100000;
	npc->AddAnimation(anim);

	anim.animName = "JumpRight";
	anim.startAnim = 6;
	anim.endAnim = 6;
	anim.loop = true;
	anim.frameTime = 0;
	npc->AddAnimation(anim);

	anim.animName = "JumpLeft";
	anim.startAnim = 33;
	anim.endAnim = 33;
	anim.loop = true;
	anim.frameTime = 0;
	npc->AddAnimation(anim);

	anim.animName = "FallRight";
	anim.startAnim = 7;
	anim.endAnim = 7;
	anim.loop = false;
	anim.frameTime = 0;
	npc->AddAnimation(anim);

	anim.animName = "FallLeft";
	anim.startAnim = 32;
	anim.endAnim = 32;
	anim.loop = false;
	anim.frameTime = 0;
	npc->AddAnimation(anim);

}