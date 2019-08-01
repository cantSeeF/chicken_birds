#pragma once
#include "cocos2d.h"
#include "Chicken.h"

using namespace cocos2d;

class Eagle : public Sprite {
public:
	Eagle();
	~Eagle();
	bool virtual init();
	CREATE_FUNC(Eagle);
	Animate* createAnimate(ActionState tobeState);
	void myUpdate(float dt);
	void birdFly();
	//前一帧y速度
	int getSpeed();
	void update(float t);
private:
	int _speed;
	bool changeState(ActionState state);
	unsigned int _isFirstTime;
	Action *_birdFlyAction;
	ActionState _currentStatus;
	Point _origin;
	Size _visiableSize;
};