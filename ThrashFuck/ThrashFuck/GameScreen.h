#pragma once

#include <Engine\Application.hpp>
#include <Engine\ResourceManager.hpp>
#include <Engine\TileMap.hpp>
#include <Engine\Camera.hpp>
#include <Engine\Font.hpp>
#include <Engine\Config.hpp>
#include <Engine\Timer.hpp>

const int GameWindowWidth = 1024;
const int GameWindowHeight = 768;

const int m_ninjatile[6] = { 0,64,128,256,320,386 };

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

	void AddObject(std::string name, double x, double y, double w, double h, bool stat);
private:
	TextureManager* m_textures;
	Font* m_font;
	FontField m_fontfield1;
	FontField m_fontfield2;
	FontField m_fontfield3;
	FontField m_fontfield4;
	TileMap* m_world;
	Camera* m_camera;
	Object* m_player;
	Object* m_ninja;
	Config* m_configFile;
	Timer m_timer;
	double m_avgfps;
	double m_angle;
	Vector m_size;
	int m_incsize;

	int m_drawtitle;

	int m_tileid;
};

