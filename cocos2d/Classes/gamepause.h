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

	//������Ϸ  
	void menuContinueCallback(Ref* pSender);
	//���عؿ�����
	void menuBackCallback(Ref* pSender);
	void valueChanged(Ref *sender,Control::EventType controlEvent);
private:

};