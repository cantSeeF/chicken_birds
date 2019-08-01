#pragma once
#include "GameScene.h"
#include "LevelSelectScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace std;

class WelcomeScene : public Scene{
public:
	WelcomeScene(void);
	~WelcomeScene(void);
	bool virtual init();
	CREATE_FUNC(WelcomeScene);
	void menuStartCallback(Object *sender);
	void menuMusicCallback(Object *sender);
	void menuScoreCallback(Object *sender);

	//·µ»Ø¼ü¹Ø±Õ
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
private:
	bool _isMusicOpen;
};