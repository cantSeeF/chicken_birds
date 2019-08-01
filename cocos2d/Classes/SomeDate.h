#pragma once

#include "cocos2d.h"
USING_NS_CC;

const int MUJI_COUNT = 3;
const int CHICKEN_LIFE = 3;

typedef enum _game_status {
	GAME_STATUS_START = 1,
	GAME_STATUS_STAY,
	GAME_STATUS_OVER,
	GAME_STARUS_WIN
} GameStatus;

