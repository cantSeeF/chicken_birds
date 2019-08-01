#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include "GameLayer1.h"
#include "GameLayer2.h"
#include "GameLayer3.h"
#include "GameLayer4.h"
#include "GameLayer5.h"
#include "GameLayer6.h"
#include "GameLayer7.h"
#include "GameLayer8.h"
#include "GameLayer9.h"
#include "BackgroundLayer.h"
#include "StatusLayer.h"

using namespace cocos2d;

class GameScene :public Scene{
public:
	GameScene();

	~GameScene();

	bool virtual init();

	void restart();

	CREATE_FUNC(GameScene);
};