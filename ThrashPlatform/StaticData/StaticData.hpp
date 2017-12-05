#pragma once
#include "../GameScreen.h"

static int CreateNpcFactory(NpcFactory* factory, GameScreen* screen);

static int CreateObjectFactory(ObjectFactory* factory, GameScreen* screen);

static int CreateAnimations(ThrashEngine::AnimationFactory* factory, GameScreen* screen);

static int CreateGameSystem(GameScreen* screen);

static int CreateInitGamesStaticData(GameScreen* screen);

static int LoadConfigs(GameScreen* screen, std::string configPath);

static int CreateGameGUI(GameScreen*);
