#pragma once
#include "GameScene.h"
#include "WelcomeScene.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace std;

class LevelSelectScene : public Scene{
public:
	LevelSelectScene(void);
	~LevelSelectScene(void);
	bool virtual init();
	CREATE_FUNC(LevelSelectScene);
	void menuLevel1Callback(Object *sender);
	void menuLevel2Callback(Object *sender);
	void menuLevel3Callback(Object *sender);
	void menuLevel4Callback(Object *sender);
	void menuLevel5Callback(Object *sender);
	void menuLevel6Callback(Object *sender);
	void menuLevel7Callback(Object *sender);
	void menuLevel8Callback(Object *sender);
	void menuLevel9Callback(Object *sender);

	void menuMusicCallback(Object *sender);

	//·µ»Ø¼ü¹Ø±Õ
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
private:
	bool _isMusicOpen;
};