#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
//#include "extensions\cocos-ext.h"
//#include "LevelSelectScene.h"

//using namespace CocosDenshion;
using namespace cocos2d::extension;
USING_NS_CC;

class GamePause : public Layer
{
public:
	virtual bool init();
	static Scene* scene(RenderTexture* sqr);
	CREATE_FUNC(GamePause);

	//继续游戏  
	void menuContinueCallback(Ref* pSender);
	//返回关卡界面
	void menuBackCallback(Ref* pSender);
	void valueChanged(Ref *sender,Control::EventType controlEvent);
private:

};