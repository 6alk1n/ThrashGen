#pragma once

#include <Engine\Application.hpp>
#include <Engine\Sprite.hpp>
#include <Engine\ResourceManager.hpp>
#include <Engine\ObjectManager.hpp>
#include <Engine\TileMap.hpp>
#include <Engine\Camera.hpp>
#include <Engine\Font.hpp>
#include <string>
class Game : public ThrashEngine::Application
{
public:
	Game();
	~Game();

	virtual ThrashEngine::ResultState Draw() override;
	virtual ThrashEngine::ResultState Update() override;
	virtual ThrashEngine::ResultState OnInit()override;
	virtual ThrashEngine::ResultState OnShutdown()override;

	void RestartGame();
	void AddObject(std::string name, double x, double y, bool stat);
protected:
	ThrashEngine::Object* m_player;
	ThrashEngine::TextureManager* m_textures;
	ThrashEngine::TileMap* m_world;
	ThrashEngine::Camera* m_camera;
	ThrashEngine::Font* m_font;
	ThrashEngine::FontField m_debug1;
};