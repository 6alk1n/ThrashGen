#include "Game.hpp"
#include <Engine/Physics.hpp>
#include <iostream>
#include <Engine/Object.hpp>
Game::Game()
{
}

Game::~Game()
{

}

ThrashEngine::ResultState Game::Draw()
{
	m_world->Draw(m_graphics);

	/*SDL_Color col;
	col.r = 255;
	col.g = 255;
	col.b = 255;
	col.a = 255;
	SDL_Texture* text = m_font->RenderTexture(m_graphics, "Text", col);
	SDL_Rect rect;
	rect.x = 400;
	rect.y = 300;g
	rect.w = 64;
	rect.h = 32;
	m_graphics->DrawTexture(text, &rect);*/
	m_debug1.ClearField();
	m_debug1 << "Player position [" << m_player->GetX() << " : " << m_player->GetY() << "]"<<"\n";
	m_debug1 << "Object count: " << m_world->GetObjectCount();
	m_debug1 << "Collisions: " << m_world->m_collisions.size();
	m_debug1.Render();
	
	return ThrashEngine::ResultState::Success;
}

ThrashEngine::ResultState Game::Update()
{
	if (m_input->OnUp(SDLK_ESCAPE))
	{
		m_done = true;
	}
	if (m_input->OnDown(SDLK_1))
	{
		m_graphics->SetViewPort("default");
	}
	if (m_input->OnDown(SDLK_2))
	{
		m_graphics->SetViewPort("DrawScreen1");
	}
	if (m_input->IsPressed(SDLK_w))
	{
		m_player->Force(0.0, -3.0);
	}
	if (m_input->IsPressed(SDLK_s))
	{
		m_player->Force(0.0, 3.0);
	}
	if (m_input->IsPressed(SDLK_a))
	{
		m_player->Force(-3.0, 0.0);
	}
	if (m_input->IsPressed(SDLK_d))
	{
		m_player->Force(3.0, 0.0);
	}
	if (m_input->IsPressed(ThrashEngine::MOUSE_RIGHT))
	{
		std::cout << m_input->GetMouseX() << " ; " << m_input->GetMouseY() << std::endl;
	}
	if (m_input->OnDown(ThrashEngine::MOUSE_LEFT))
	{
		//create new object
		ThrashEngine::Vector mouse = m_input->GetMousePos();
		mouse -= m_player->GetPos();
		mouse += m_camera->GetPos();
		mouse.Normalize();
		ThrashEngine::Vector projectile = m_player->GetPos() + mouse*40;

		ThrashEngine::Object* project = m_world->CreateObject("ball");
		project->SetPos(projectile);
		project->SetVel(mouse);
		
	}
	m_world->Update(1.0);
	m_player->Update();
	m_camera->Center(m_player->GetPos());



	return ThrashEngine::ResultState::Success;
}

ThrashEngine::ResultState Game::OnInit()
{
	m_textures = new ThrashEngine::TextureManager(m_graphics);
	m_textures->SetColorKey(m_graphics->GetColor(113, 38, 38));
	m_world = new ThrashEngine::TileMap;
	m_world->AddHeader("PlayerSprite", 32, 32, m_textures->GetTexture("Assets/1.bmp"), 0, 0, 256, 256);
	m_world->AddHeader("empty", 0, 0, m_textures->GetTexture("Assets/empty.bmp"), 0, 0, 0, 0);
	m_textures->SetColorKey(m_graphics->GetColor(255, 255, 255));
	m_world->AddHeader("ball", 32, 32, m_textures->GetTexture("Assets/ball.bmp"), 0, 0, 32, 32);
	m_player = m_world->CreateObject("PlayerSprite");
	m_player->SetPos(400, 300);
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 800;
	rect.h = 600;
	m_graphics->CreateViewPort(std::string("DrawScreen1"), rect);
	m_graphics->SetViewPort(std::string("DrawScreen1"));
	m_world->AddHeader("floor", 32, 32,m_textures->GetTexture("Assets/Lightwood64.bmp") , 0, 0, 64, 64);
	m_world->Create(15, 15, 32, 32);
	for (int i = 0; i < 15; i++)
	{
		for (int n = 0; n < 15; n++)
		{
			m_world->CreateTileObject("floor", i, n);
			m_world->m_tiles[i + n * 15]->SetPos(i * 32, n * 32);
			m_world->m_tiles[i + n * 15]->SetCollision(false);
		}
	}
	m_world->m_tiles[0 + 0 * 15]->SetCollision(true);
	m_world->m_tiles[0 + 5 * 15]->SetCollision(true);
	m_world->m_tiles[0 + 10 * 15]->SetCollision(true);
	ThrashEngine::Object* ptr =m_world->CreateObject("PlayerSprite");
	ptr->SetPos(300, 250);
	m_camera = new ThrashEngine::Camera();
	m_camera->SetPos(ThrashEngine::Vector(0, 0));
	m_camera->SetView(ThrashEngine::Vector(800, 600));
	m_camera->SetScale(1.0);
	m_world->SetCamera(m_camera);
	m_font = new ThrashEngine::Font;
	m_font->LoadFont("Assets/font.ttf", 16);
	m_debug1.SetFont(m_font);
	m_debug1.SetGraphics(m_graphics);
	m_debug1.SetPos(ThrashEngine::Vector(0, 0));
	m_debug1.SetSize(ThrashEngine::Vector(600, 32));
	SDL_Color col;
	col.r = 0;
	col.g = 255;
	col.b = 255;
	col.a = 255;
	m_debug1.SetColor(col);
	m_world->UpdateCollisionTimeSet(60);




	return ThrashEngine::ResultState::Success;
}

ThrashEngine::ResultState Game::OnShutdown()
{
	m_textures->Clear();
	m_world->Clear();
	return ThrashEngine::ResultState::Success;
}


void Game::RestartGame()
{

}