#pragma once
#include "cocos2d.h"
#include "Chicken.h"

using namespace cocos2d;

class RedBird : public Sprite {
public:
	RedBird();
	~RedBird();
	bool virtual init();
	CREATE_FUNC(RedBird);
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