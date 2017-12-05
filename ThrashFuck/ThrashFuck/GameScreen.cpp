#include "GameScreen.h"

using namespace ThrashEngine;

GameScreen::GameScreen()
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
	SDL_Rect rect;
	rect.x = 1024/2-512/2+100;
	rect.y = 768/2-512/2+50;
	rect.h = m_size.y;
	rect.w = m_size.x;
	SDL_Point p;
	p.x = m_size.x/2;
	p.y = m_size.y/2;
	SDL_RenderCopyEx(m_graphics->GetRenderer(), m_player->GetTexture(), NULL, &rect, m_angle,&p, SDL_FLIP_NONE);

	m_fontfield1.ClearField();
	m_fontfield1 << "HE IS WAITING FOR YOU TO JOIN OUR BAND!";
	m_fontfield1.Render();
	m_ninja->SetUV(m_ninjatile[m_tileid], 0, m_ninjatile[m_tileid] + 64, 64);
	if (m_drawtitle)
	{
		m_fontfield2.ClearField();
		m_fontfield2 << "CALL RIGHT NOW 8-800-555-35-35!!!";
		m_fontfield2.Render();
	}

	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::Update()
{

	static unsigned int m_avgt = 0;
	static unsigned int m_avgc = 0;
	m_avgt += m_timer.End();

	//m_camera->Center(m_player->GetPos());
	m_world->Update(1.0);


	m_avgc++;
	if (m_avgt > 300 && !m_drawtitle)
	{
		m_avgfps = m_avgt*m_avgc / 1000;
		m_avgt = 0;
		m_avgc = 0;
		if (m_drawtitle)
			m_drawtitle = 0;
		else m_drawtitle = 1;
	}
	if (m_avgt > 700 && m_drawtitle)
	{
		m_avgfps = m_avgt*m_avgc / 1000;
		m_avgt = 0;
		m_avgc = 0;
		if (m_drawtitle)
			m_drawtitle = 0;
		else m_drawtitle = 1;
	}
	m_angle++;
	if (m_incsize)
	{
		m_size.x += 10;
		m_size.y += 10;
		if (m_size.x > 500)
		{
			m_incsize = 0;
		}
	}
	else
	{
		m_size.x -= 10;
		m_size.y -= 10;
		if (m_size.x < 100)
		{
			m_incsize = 1;
		}
	}
	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::OnInit()
{
	m_textures = new ThrashEngine::TextureManager(m_graphics);
	m_textures->SetColorKey(m_graphics->GetColor(255, 255, 255));
	m_world = new ThrashEngine::TileMap;
	m_world->UpdateCollisionTimeSet(60);
	m_world->AddHeader("PlayerSprite", 512, 512, m_textures->GetTexture("Data/Sprites/Superchlen.bmp"), 0, 0, 512, 512);
	m_world->AddHeader("ninja", 64, 64, m_textures->GetTexture("Data/Sprites/blue_ninja.bmp"), 0, 0, 640, 256);
	m_player = m_world->CreateObject("PlayerSprite");
	m_player->SetPos(256, 128);
	m_player->SetActive(false);
	m_ninja = m_world->CreateObject("ninja");
	m_ninja->SetPos(50, 700);
	
	m_camera = new Camera;
	m_camera->SetView(Vector(1024, 768));
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
	m_fontfield1.SetPos(ThrashEngine::Vector(100, 0));
	m_fontfield1.SetSize(ThrashEngine::Vector(800, 32));
	m_fontfield1.SetColor(col);
	col.r = 255;
	col.g = 0;
	col.b = 0;
	col.a = 255;
	m_fontfield2.SetFont(m_font);
	m_fontfield2.SetGraphics(m_graphics);
	m_fontfield2.SetPos(ThrashEngine::Vector(100, 32));
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

	ThrashEngine::Config m_configFile;
	std::cout << "Loading Data/config.cfg" << std::endl;
	if (!m_configFile.LoadConfig("Data/config.cfg"))
	{
		std::cout << "Failed to load config file" << std::endl;


	}
	else {
		m_configFile.SetGroup("Game");
		m_configFile.SetGroup("Window");
		ThrashEngine::ConfigData ScreenX = m_configFile.GetParam("ScreenWidth");
		ThrashEngine::ConfigData ScreenY = m_configFile.GetParam("ScreenHeight");

		m_window->ResizeWindow(ScreenX.data, ScreenY.data);

		//Set renderer scale
		m_graphics->SetRendererScale(ScreenX.data / GameWindowWidth, ScreenY.data / GameWindowHeight);

	}
	m_timer.Start();
//	m_supertim.Start();
	m_avgfps = 0;

	m_angle = 0;
	m_size=Vector(250,250);
	m_incsize = 1;
	m_drawtitle = 1;
	m_tileid = 0;
	return ResultState::Success;
}
ThrashEngine::ResultState GameScreen::OnShutdown()
{
	return ResultState::Success;
}
