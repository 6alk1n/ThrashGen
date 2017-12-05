#include "GameScreen.h"

#include <Engine/Utility.hpp>
#include <Engine/Physics.hpp>
#include "ConsoleCommands.hpp"
#include "StaticData/StaticData.cpp"
using namespace ThrashEngine;
//note:test comment
//ulala
//super gamescreen test

GameScreen::GameScreen():Application()
{
}


GameScreen::~GameScreen()
{

}


ThrashEngine::ResultState GameScreen::Draw()
{
	m_monitor.StartMonitor("Drawing_WorldDraw");
	
	m_world->Draw(m_graphics,-m_camera->GetPos().x,-m_camera->GetPos().y);
	
	double debugmode = AppParams.GetDouble("debugmode");
	if (debugmode)
	{
		for (auto i = m_world->collisions.begin(); i != m_world->collisions.end(); i++)
		{
			if (i->obj1 == m_player)
			{
				m_graphics->SetColor(255, 0, 0, 255);
				m_graphics->DrawRectOut(i->obj2->m_pos.x - m_camera->GetPos().x, i->obj2->m_pos.y - m_camera->GetPos().y, i->obj2->m_pos.w, i->obj2->m_pos.h);
			}
		}
	}
	m_monitor.EndMonitor("Drawing_WorldDraw");

	DrawGUIText();

	if (m_levelEditorState)
	{
		m_graphics->SetColor(255, 0, 0, 255);
		SDL_Rect pos,uv;
		//Selector
		for (int n=0;n<m_guiparams.LevelEditorCellRow;n++)
		for (int i = 0; i < m_guiparams.LevelEditorCellColumn; i++)
		{
			m_graphics->DrawRectOut(m_guiparams.LevelEditorTableX+i*m_guiparams.LevelEditorCellX, m_guiparams.LevelEditorTableY+n*m_guiparams.LevelEditorCellY, m_guiparams.LevelEditorCellX, m_guiparams.LevelEditorCellY);
			if (LevelEditorSelectorItems[n*m_guiparams.LevelEditorCellColumn + i]) {
				LevelEditorSelectorItems[n*m_guiparams.LevelEditorCellColumn + i]->m_textureUV; // ???
				pos.x = m_guiparams.LevelEditorTableX + i*m_guiparams.LevelEditorCellX;
				pos.y = m_guiparams.LevelEditorTableY + n*m_guiparams.LevelEditorCellY;
				pos.w = m_guiparams.LevelEditorCellX;
				pos.h = m_guiparams.LevelEditorCellY;
				uv.x = 0;
				uv.y = 0;
				uv.w = LevelEditorSelectorItems[n*m_guiparams.LevelEditorCellColumn + i]->m_textureUV.w;
				uv.h = LevelEditorSelectorItems[n*m_guiparams.LevelEditorCellColumn + i]->m_textureUV.h;
				if (LevelEditorSelectorItems[n*m_guiparams.LevelEditorCellColumn + i]->m_texture) m_graphics->DrawTexture(LevelEditorSelectorItems[n*m_guiparams.LevelEditorCellColumn + i]->m_texture, &pos, &uv);
			}
		}
		//Properties
		m_graphics->SetColor(128, 128, 128,255);
		//int paramx = LevelEditorTableX + LevelEditorCellX*(LevelEditorCellColumn + 1);
		m_graphics->DrawRectXY(m_guiparams.LevelEditorParamX, m_guiparams.LevelEditorParamY, m_window->GetScreenWidth(), m_window->GetScreenHeight());
		
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
			pos.x = (m_guiparams.LevelEditorParamX + m_window->GetScreenWidth())/2 - 32;
			pos.y = m_guiparams.LevelEditorParamY + 32;
			pos.w = 64;
			pos.h = 64;

			uv.x = selected->m_textureUV.x;
			uv.y = selected->m_textureUV.y;
			uv.w = selected->m_textureUV.w;
			uv.h = selected->m_textureUV.h;

			m_graphics->DrawTexture(selected->m_texture, &pos, &uv);
			m_nameField.ClearField();
			Property* objName= selected->m_property->Get("Name");
			if (objName)
				m_nameField << objName->value;
			else
				m_nameField << "NONAMEOBJECT";
			m_nameField.Render();		
			Vector mousepos = m_input->GetMousePos();
			pos.x = mousepos.x;
			pos.y = mousepos.y;
			pos.w = m_SpinButtonWidth.GetValue();
			pos.h = m_SpinButtonHeight.GetValue();

			if (selected!=m_selectedObject)
			m_graphics->DrawTexture(selected->m_texture, &pos, &uv);

			m_SpinButtonWidth.m_active = true;
			m_SpinButtonHeight.m_active=true;
		}
		else
		{

			m_SpinButtonWidth.m_active=false;
			m_SpinButtonHeight.m_active=false;
		}

	}

	m_monitor.StartMonitor("Drawing_GUIDraw");
	m_gui.Draw();
	m_monitor.EndMonitor("Drawing_GUIDraw");

	/***
	
	Light
	
	**/
//	SDL_Texture* light = SDL_GetRenderTarget(m_graphics->GetRenderer());

	//m_console.Draw(m_graphics);

	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::DrawGUIText()
{
	double debugmode = AppParams.GetDouble("debugmode");
	m_monitor.StartMonitor("Drawing_TextDraw");
	if (debugmode) {
		m_playerstats_text.ClearField();
		m_playerstats_text << "Mouse delta [" << m_input->GetDeltaX() << " : " << m_input->GetDeltaY() << "]";
		m_playerstats_text << "    Object count: " << m_world->objects.size();
		m_playerstats_text << "    Collisions: " << m_world->collisions.size();
		m_playerstats_text.EndLine();
		m_playerstats_text << "Player velocity [" << m_player->m_vel.x << " : " << m_player->m_vel.y << "]  ";
		m_playerstats_text << "Sounds player:" << m_soundManager->GetSounds()->size();
		m_playerstats_text.EndLine();
		m_playerstats_text << "SlowDownSpeed : " << m_slowdownVel;
		m_playerstats_text << " Jump Velocity : " << m_jumpVel;

		m_playerstats_text << " Gravity Y: " << m_gravity;
		m_playerstats_text << " CanJump? ";
		if (m_player->m_property->GetDouble("CanJump")) m_playerstats_text << "Yes";
		else m_playerstats_text << "No";
		m_playerstats_text << " FPS: " << m_avgfps;
		m_playerstats_text.EndLine();
		m_playerstats_text << "Left/Right arrow keys to move. Space to jump. r - reset position. t - reset velocity.";
		m_playerstats_text.EndLine();
		m_playerstats_text.Render();

		m_monitorField.ClearField();
	}
	double totaltime = m_monitor.GetMonitor("Toogle").diffTime * 1000;
	double drawtime = m_monitor.GetMonitor("DrawingFrame").diffTime * 1000;
	double updatetime = m_monitor.GetMonitor("UpdatingFrame").diffTime * 1000;
	double drawworldtime = m_monitor.GetMonitor("Drawing_WorldDraw").diffTime * 1000;
	double drawtexttime = m_monitor.GetMonitor("Drawing_TextDraw").diffTime * 1000;
	double drawguitime = m_monitor.GetMonitor("Drawing_GUIDraw").diffTime * 1000;
	if (debugmode) {
		m_monitorField << "Total: " << totaltime <<
			" ms| DrawingFrame: " << drawtime << " ms, " << (drawtime / totaltime) * 100 << "%" <<
			"| UpdatingFrame: " << updatetime << " ms, " << (updatetime / totaltime) * 100 << "%";
		m_monitorField.EndLine();
		m_monitorField << "---> World Draw: " << drawworldtime << " ms, " << (drawworldtime / drawtime) * 100 << "%";
		m_monitorField << "| Text Draw: " << drawtexttime << " ms, " << (drawtexttime / drawtime) * 100 << "%";
		m_monitorField << "| GUI Draw: " << drawguitime << " ms, " << (drawguitime / drawtime) * 100 << "%";
		m_monitorField.Render();
	}
	m_monitor.EndMonitor("Drawing_TextDraw");
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
		m_player->m_vel+=(Vector(m_acceleration, 0));
 		m_player->SetAnimation("PlayerMoveRight");
		controlled++;
		moveside = 1;
	}
	if (m_input->IsPressed(SDLK_LEFT))
	{
		m_player->m_vel+=(Vector(-m_acceleration, 0));
		m_player->SetAnimation("PlayerMoveLeft");
		controlled++;
		moveside = -1;
	}
	if (m_input->IsPressed(SDLK_UP))
	{
		m_player->m_vel += (Vector(0, -m_acceleration));
		m_player->SetAnimation("PlayerMoveRight");
		controlled++;
		moveside = 1;
	}	
	if (m_input->IsPressed(SDLK_DOWN))
	{
		m_player->m_vel += (Vector(0, m_acceleration));
		m_player->SetAnimation("PlayerMoveRight");
		controlled++;
		moveside = 1;
	}
	if (m_player->m_property->GetDouble("CanJump")) {
		if (m_input->IsPressed(SDLK_SPACE))
		{
			m_player->m_vel+=(Vector(0, -m_jumpVel));
			m_player->m_property->Set("CanJump", 0);
			controlled++;
		}
	}
	if (!controlled)
	{
		if(moveside==1)m_player->SetAnimation("StandRight");
		else if(moveside==-1)m_player->SetAnimation("StandLeft");
	}
	if (m_player->m_vel.y > 0)
	{
		if (moveside == 1)m_player->SetAnimation("FallRight");
		if (moveside == -1)m_player->SetAnimation("FallLeft");
	}
	else if (m_player->m_vel.y < 0)
	{
		if (moveside == 1)m_player->SetAnimation("JumpRight");
		if (moveside == -1)m_player->SetAnimation("JumpLeft");
	}
	if (m_input->IsPressed(SDLK_r))
	{
		m_player->m_pos = Vector (50, 50);
	}
	if (m_input->IsPressed(SDLK_t))
	{
		m_player->m_vel=Vector(0, 0);
	}
	if (m_input->OnDown('`'))
	{
		m_console.SetActiveLabel(!m_console.GetActiveLabel());
		if (m_console.GetActiveLabel())
		{
			m_gui.SetActiveGUIObject(&m_console.m_inputlabel);
		}
	}
	

	if (m_input->OnDown(MOUSE_LEFT))
	{
		std::cout << m_input->GetMouseX() << " : " << m_input->GetMouseY() << std::endl;
		m_input->SetScale(1, 1);
		std::cout << m_input->GetMouseX() << " : " << m_input->GetMouseY() << std::endl;
		m_input->SetScale(m_guiparams.ScalingWidth, m_guiparams.ScalingHeight);
	}

	//Camera scrolling and interacting
	if (m_levelEditorState)
	{
		Vector mousepos = m_input->GetMousePos();
		if (mousepos.x < m_guiparams.EditorMouseBorderScroll) m_camera->Move(Vector(-m_guiparams.EditorMouseScroll, 0));
	//	else if (mousepos.x >m_window->GetScreenWidth()-10) m_camera->Move(Vector(EditorMouseScroll, 0));
		else if (mousepos.x >(m_window->GetScreenWidth()/ m_guiparams.ScalingWidth) - 10) m_camera->Move(Vector(m_guiparams.EditorMouseScroll, 0));
		if (mousepos.y < m_guiparams.EditorMouseBorderScroll) m_camera->Move(Vector(0, -m_guiparams.EditorMouseScroll));
		else if (mousepos.y >(m_window->GetScreenHeight()/ m_guiparams.ScalingHeight) - 10) m_camera->Move(Vector(0, m_guiparams.EditorMouseScroll));

		if (m_input->OnDown(MOUSE_LEFT))
		{
			ThrashEngine::Rectangle rectParam (m_guiparams.LevelEditorParamX, m_guiparams.LevelEditorParamY, (m_window->GetScreenWidth() / m_guiparams.ScalingWidth), (m_window->GetScreenHeight() / m_guiparams.ScalingHeight));
			ThrashEngine::Rectangle rectList(m_guiparams.LevelEditorTableX, m_guiparams.LevelEditorTableY, m_guiparams.LevelEditorCellX*m_guiparams.LevelEditorCellColumn, m_guiparams.LevelEditorCellY*m_guiparams.LevelEditorCellRow);
			ThrashEngine::Rectangle rectButton(0, 768 - 96, 64, 96);
			if (!isPointinRect(mousepos, rectParam) && !isPointinRect(mousepos, rectList) && !isPointinRect(mousepos, rectButton)) {
				{
					if (m_selectedItem > 0 && LevelEditorSelectorItems[m_selectedItem] && m_selectedItem < m_guiparams.LevelEditorCellColumn*m_guiparams.LevelEditorCellRow) {
						ThrashEngine::Object* newObject=nullptr;
						unsigned int virtlvl = LevelEditorSelectorItems[m_selectedItem]->GetVirtualizationLevel();
						if (virtlvl == VirtualLevelObject)
						{
							newObject = new ThrashEngine::Object(LevelEditorSelectorItems[m_selectedItem]);
						}
						else if (virtlvl == VirtualLevelAnimationObject)
						{
							newObject = new ThrashEngine::AnimationObject();
							*newObject = *LevelEditorSelectorItems[m_selectedItem];
						}
						else if (virtlvl = VirtualLevelNPC)
						{
							newObject = new ThrashEngine::NPC();
							*newObject = *LevelEditorSelectorItems[m_selectedItem];
						}

						newObject->m_active=true;
						newObject->m_debug=true;
						newObject->m_static = false;
						newObject->SetSize(m_SpinButtonWidth.GetValue(), m_SpinButtonHeight.GetValue());
						newObject->m_pos = (mousepos+m_camera->GetPos());
						m_world->AddObject(newObject);

						//if (LevelEditorSelectorItems[m_selectedItem]->GetVirtualState() == VirtualLevelObject) //is object
						{
							//	ThrashEngine::Object* obj = m_world->CreateObject(LevelEditorSelectorItems[m_selectedItem]->m_property.Get("Name")->value);
							//	obj->m_active=true;
							//	obj->m_debug=true;
							//	obj->SetSize(m_SpinButtonWidth.GetValue(), m_SpinButtonHeight.GetValue());
							//	obj->m_pos = (mousepos+m_camera->GetPos());
						}
						//else
						{
							//	if (LevelEditorSelectorItems[m_selectedItem]->GetVirtualState() == VirtualLevelNPC)
							{
								/*NPC* newenemy = CreateNPC(LevelEditorSelectorItems[m_selectedItem]->GetName(), m_world);
								newenemy->m_pos = (mousepos + m_camera->GetPos());
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
								newenemy->EnableAI(true);*/
							}
						}
					}
					//	else
					{
						for (auto i = m_world->objects.begin(); i != m_world->objects.end(); i++)
						{
							if (isPointinRect(mousepos + m_camera->GetPos(), (*i)->m_pos))
							{
								m_selectedObject = (Object*)(*i);
								m_SpinButtonWidth.SetValue(m_selectedObject->m_pos.w);
								m_SpinButtonHeight.SetValue(m_selectedObject->m_pos.h);
								break;
							}
						}
					}
				}
			}
		}
		if ((m_input->IsPressed(MOUSE_LEFT) && m_selectedObject))
		{
			if (isPointinRect(mousepos + m_camera->GetPos(), m_selectedObject->GetRect()) || (isPointinRect(mousepos + m_camera->GetPos() - Vector(m_input->GetDeltaX(), m_input->GetDeltaY()), m_selectedObject->GetRect())))
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
//	m_player->m_vel+=Vector(0.0, (m_gravity)); //gravity
	if (abs(m_player->m_vel.x)> m_playerMaxSpeed)
	{
		if (m_player->m_vel.x>0) m_player->m_vel.x=m_playerMaxSpeed;
		else m_player->m_vel.x=-m_playerMaxSpeed;
	}
	if (abs(m_player->m_vel.y)> m_playerMaxYSpeed)
	{
		if (m_player->m_vel.y>0) m_player->m_vel.y=m_playerMaxYSpeed;
		else m_player->m_vel.y=-m_playerMaxYSpeed;
	}
	if(!m_levelEditorState)
	m_world->Update(1.0);
	
	if (abs(m_player->m_vel.x )<0.1) m_player->m_vel.x=0;
	else if (m_player->m_vel.x>0) m_player->m_vel+=-m_slowdownVel;
	else  m_player->m_vel+=m_slowdownVel;
	m_avgc++;
	if (m_avgt > 1000)
	{
		m_avgfps = m_avgt*m_avgc /1000;
		m_avgt = 0;
		m_avgc = 0;
	}
	m_gui.Update(1.0);
	m_soundManager->Update();

	std::string input_text = m_inputlabel.GetInputLabel();
	if (input_text != "")
	{
		std::cout << input_text << std::endl;
	}

	//Do developer console handling
	std::string console_text = m_console.m_inputlabel.GetInputLabel();
	if (console_text != "") HandleConsoleCommand(this, &console_text);
	
	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::OnInit()
{
	CreateGameSystem(this);

	CreateInitGamesStaticData(this);
	//m_levelreader.SaveAnimationHeader(m_animFactory, "Data/Animations.anm");
	m_levelreader.SaveHeader(m_objectFactory, m_animobjectFactory, m_npcFactory, "Data/objectHeader.def", m_textures);
	m_objectFactory->Clear(); m_animobjectFactory->Clear(); m_npcFactory->Clear();

	std::cout << "File checksums:" << std::endl;
	std::cout << "'Data/objectHeader.def' - " << Utility::CheckSum("Data/objectHeader.def") <<" - "<<Utility::NumToHex(Utility::CheckSum("Data/objectHeader.def")) <<std::endl;
	std::cout << "'Data/Animations.anm' - " << Utility::CheckSum("Data/Animations.anm") << " - " << Utility::NumToHex(Utility::CheckSum("Data/Animations.anm")) << std::endl;
	
	m_levelreader.ReadAnimationHeader(m_animFactory, "Data/Animations.anm");
	m_levelreader.ReadHeader(m_objectFactory, m_animobjectFactory, m_npcFactory, "Data/objectHeader.def", m_textures);

	//Unite headers with animations
	m_animobjectFactory->SetAnimations(m_animFactory);
	m_npcFactory->SetAnimations(m_animFactory);

	if (m_levelreader.LoadLevel(m_world, "Data/levelsave1.lvl", m_textures));
	else
	{
		std::cout << "Unable to load Data/levelsave1.lvl" << std::endl;
		m_levelreader.ReadHeader(m_world, "Data/ObjectTypes.txt", m_textures);
		m_levelreader.ReadHeader(m_world, "Data/ObjectTyped.txt", m_textures);
	}
/*	if (m_levelreader.ReadLevel(m_world, m_animFactory,m_objectFactory,m_animobjectFactory,m_npcFactory,"Data/world_test.lvl", m_textures))
	{
		std::cout << "Loaded Data/world_test.lvl" << std::endl;
	}
	else
	{
		std::cout << "Unable to load Data/world_test.lvl" << std::endl;
		m_levelreader.ReadHeader(m_world, "Data/ObjectTypes.txt", m_textures);
		m_levelreader.ReadHeader(m_world, "Data/ObjectTyped.txt", m_textures);
	}*/
	/*
	ThrashEngine::Animation anim;
	m_player->SetUVCell(46, 50);*/

	//Create player
	m_player = m_npcFactory->CreateNpc("Player");
//	m_player->m_property->Set("CanJump", 0);
	m_player->m_pos = Vector(50, 50);
	m_player->SetAnimation("PlayerStandRight");
	m_player->m_loopAnimation = true;
	AddAnimaton(m_player);
	m_player->EnableAI(false);
	m_player->m_static=(false);

	m_world->AddObject(m_player);

	m_camera = new Camera;
	m_camera->SetView(Vector(1024, 768));
	m_camera->Center(m_player->m_pos.GetVector());

	CreateGameGUI(this);
	LoadConfigs(this, "Data/config.cfg");

//	m_levelreader.AddPropertyToLevel(m_player);
//	m_levelreader.SaveLevel(m_world, "Data/world.lvl");

	//Level editor GUI stuff

	LevelEditorSelectorItems = new Object*[m_guiparams.LevelEditorCellColumn*m_guiparams.LevelEditorCellRow];
	for (int i = 0; i < m_guiparams.LevelEditorCellColumn*m_guiparams.LevelEditorCellRow; i++)
		LevelEditorSelectorItems[i] = nullptr;

	LevelEditorSelectorItems[2] = m_objectFactory->CreateObject("WoodPlatform");
	LevelEditorSelectorItems[2]->m_active=(false);	
	LevelEditorSelectorItems[2]->m_collideable=(false);
	LevelEditorSelectorItems[2]->m_debug=(false);
	LevelEditorSelectorItems[2]->m_pos = Vector(-1000,-1000);

	m_levelreader.AddFreeSave(LevelEditorSelectorItems[2]);

	LevelEditorSelectorItems[1] = m_objectFactory->CreateObject("GrassPlatform");
	LevelEditorSelectorItems[1]->m_active=(false);
	LevelEditorSelectorItems[1]->m_collideable = (false);
	LevelEditorSelectorItems[1]->m_debug=(false);
	LevelEditorSelectorItems[1]->m_pos = Vector(-1000, -1000);

	m_levelreader.AddFreeSave(LevelEditorSelectorItems[1]);

	LevelEditorSelectorItems[10] = m_npcFactory->CreateNpc("Player");
	LevelEditorSelectorItems[10]->m_active=(false);
	LevelEditorSelectorItems[10]->m_collideable = (false);
	LevelEditorSelectorItems[10]->m_debug=(false);
	LevelEditorSelectorItems[10]->m_pos = Vector(-1000, -1000);
	
	//m_levelreader.AddFreeSave(LevelEditorSelectorItems[10]);
	
	SDL_Color bordcol;
	bordcol.r = 255;
	bordcol.g = 255;
	bordcol.b = 0;
	bordcol.a = 255;
	LevelEditorSelectorButtons=new GUIButton[m_guiparams.LevelEditorCellColumn*m_guiparams.LevelEditorCellRow];
	for (int i = 0; i < m_guiparams.LevelEditorCellColumn*m_guiparams.LevelEditorCellRow; i++)
	{
		LevelEditorSelectorButtons[i].SetSize(m_guiparams.LevelEditorCellX, m_guiparams.LevelEditorCellY);
		LevelEditorSelectorButtons[i].SetFunction(&m_selectFunc);
		LevelEditorSelectorButtons[i].m_debug=(false);
		m_gui.AddGUIObject(&(LevelEditorSelectorButtons[i]));
		LevelEditorSelectorButtons[i].SetData((void*)this);	
		LevelEditorSelectorButtons[i].m_pos = Vector(m_guiparams.LevelEditorTableX+(i%m_guiparams.LevelEditorCellColumn)*m_guiparams.LevelEditorCellX, m_guiparams.LevelEditorTableY + (i/ m_guiparams.LevelEditorCellColumn) *m_guiparams.LevelEditorCellY);
		LevelEditorSelectorButtons[i].SetSize(m_guiparams.LevelEditorCellX, m_guiparams.LevelEditorCellY);
		LevelEditorSelectorButtons[i].SetBorderColor(bordcol);
		LevelEditorSelectorButtons[i].m_active=(false);
	}
	m_selectedItem = -1;

	m_SpinButtonWidth.SetFont(m_font);
	m_SpinButtonWidth.SetTexture(m_textures->GetTexture("Data/Sprites/spinbut-horizont.bmp"));
	m_SpinButtonWidth.m_pos = Vector(m_guiparams.LevelEditorParamX+10 , m_guiparams.LevelEditorParamY + 150);
	m_SpinButtonWidth.SetSize(120, 75);
	m_SpinButtonWidth.m_debug=(false);
	m_gui.AddGUIObject(&m_SpinButtonWidth);
	m_SpinButtonWidth.SetMax(500);
	m_SpinButtonWidth.SetMin(10);
	m_SpinButtonWidth.SetValue(32);
	m_SpinButtonWidth.SetStep(1);
	m_SpinButtonWidth.SetTextSizeRelative(0.7);
	m_SpinButtonWidth.m_active=(false);
	m_SpinButtonWidth.SetText("width");

	m_SpinButtonHeight.SetFont(m_font);
	m_SpinButtonHeight.SetTexture(m_textures->GetTexture("Data/Sprites/spinbut-horizont.bmp"));
	m_SpinButtonHeight.m_pos = Vector(m_guiparams.LevelEditorParamX + 140, m_guiparams.LevelEditorParamY + 150);
	m_SpinButtonHeight.SetSize(120, 75);
	m_SpinButtonHeight.m_debug=(false);
	m_gui.AddGUIObject(&m_SpinButtonHeight);
	m_SpinButtonHeight.SetMax(500);
	m_SpinButtonHeight.SetMin(10);
	m_SpinButtonHeight.SetValue(32);
	m_SpinButtonHeight.SetStep(1);
	m_SpinButtonHeight.SetTextSizeRelative(0.7);
	m_SpinButtonHeight.m_active=(false);
	m_SpinButtonHeight.SetText("height");

	//m_soundManager = new SoundManager();

	m_selectedObject = nullptr;
	m_soundBuffers->GetSoundBuffer("Data/Sounds/batman.wav");
	
	m_music = new SoundSource();
	m_music->SetBuffer(m_soundBuffers->GetSoundBuffer("Data/Sounds/Tumburag.wav"));
	alSourcei(m_music->GetSource(), AL_LOOPING, AL_TRUE);
	m_soundManager->Play(m_music);

	double vol = AppParams.GetDouble("mastervolume");
	m_soundManager->SetVolumeAll(vol);

	m_monitor.SetSubMonitorArray(60);
	m_player->m_property->Set("CanJump", 1);
	m_player->m_property->Set("TimeBetweenJump", 60.0);
	//m_window->GetScreenWidth();
	//Set input scale	
	m_guiparams.ScalingWidth = m_window->GetScreenWidth()/(double)m_guiparams.GameWindowWidth;
	m_guiparams.ScalingHeight = m_window->GetScreenHeight()/ (double)m_guiparams.GameWindowHeight;
//	if (ScalingWidth > 1) ScalingWidth = 1 / ScalingWidth;
//	if (ScalingHeight > 1) ScalingHeight = 1 / ScalingHeight;
	m_input->SetScale(m_guiparams.ScalingWidth, m_guiparams.ScalingHeight);

	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::OnShutdown()
{
	m_done = true;
	return ResultState::Success;
}

void GameScreen::AddObject(std::string name, double x, double y, double w=0, double h=0, bool stat=false)
{
	//Object* obj = m_world->CreateObject(name);
	//obj->m_pos = Vector(x, y);
	//if( w && h) obj->SetSize(w, h);
	//obj->m_static = stat;
}

void GameScreen::AddAnimaton(NPC* npc)
{
	/*ThrashEngine::Animation anim;
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
	*/
}