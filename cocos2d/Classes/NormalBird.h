#pragma once
#include "cocos2d.h"
#include "Chicken.h"

using namespace cocos2d;

class NormalBird : public Sprite {
public:
	NormalBird();
	~NormalBird();
	bool virtual init();
	CREATE_FUNC(NormalBird);
	Animate* createAnimate(ActionState tobeState);
	void myUpdate(float dt);
	void birdRun();
	void birdFly();
	//前一帧y速度
	int yLast;
	int getSpeed();
	void update(float t);
private:
	int _speed;
	bool changeState(ActionState state);
	unsigned int _isFirstTime;
	Action *_birdRunAction;
	Action *_birdFlyAction;
	ActionState _currentStatus;
};