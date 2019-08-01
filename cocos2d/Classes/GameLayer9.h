#pragma once

#include "cocos2d.h"
#include "Chicken.h"
#include "StatusLayer.h"
#include "NormalBird.h"
#include "RedBird.h"
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "egg.h"
#include "SomeDate.h"

using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

class GameLayer9 : public Layer{
public:
	GameLayer9();
	~GameLayer9();
	bool virtual init();
	void onEnter();
	void virtual onExitTransitionDidStart();
	CREATE_FUNC(GameLayer9);
	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	virtual bool onTouchBegan(Touch* touch, Event* event);
	//碰撞
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual void onContactSeparate(PhysicsContact& contact);
	//重力感应
	void onAcceleration(Acceleration* acc, Event* event);

	void update(float delta);
	//检查出屏幕
	void getbackToScreen();
	//控制鸟移动
	void chickenMoveControl();
	//加母鸡
	void addBird();
	//添加世界
	void addWorld();
	//吃蛋奖励 自定义调度器:schedule(SEL_SCHEDULE selector, float interval（每次调用时间间隔）, unsigned int repeat（次数）, float delay（第一次调用间隔）)
	void eggSurprise();
	//恢复母鸡速度
	void getBackBirdSpeed(float dt);
	//恢复母鸡
	void addABird(float dt);
	//重生
	void chickenRebirth(float dt);
	//解除无敌
	void chickenNotInvicible(float dt);
	//粒子效果
	void addParticle();
	void deathBond(Point point);
	void removeDBond();
	void gameOver();
	void gameWin();
	void showScore();
private:
	GameStatus _gameStatus;
	int _life;
	int _response;
	int _needScore;
	Chicken *_chicken;
	float _xLast;
	float _yLast;
	//放鸟
	Vector<Sprite*> _birds;
	Vector<Egg*> _eggs;
	bool _speedStatus;
	bool _isInvicible;
	Point _origin;
	Size _visiableSize;
};
