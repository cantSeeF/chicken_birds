#pragma once
#include "cocos2d.h"

using namespace cocos2d;

typedef enum{
	STATE_STAY,
	STATE_FLY,
	STATE_RUN
} ActionState;

class Chicken : public Sprite {
public:
	/**
	* Default construct
	*/
	Chicken();

	/**
	* Default distruct
	*/
	~Chicken();

	/**
	* Get instance
	*/
	static Chicken* getInstance();

	/**
	* Cocos2d construct
	*/
	bool virtual init();
	//×´Ì¬£ºÄñÔÚÅÜ
	void chickenRun();
	void chickenStay();
	void chickenFly();
	void chickenFly(bool istouch);
	Animate* createAnimate(ActionState tobeState);
	ActionState getActionState();
	//void MyUpdate(float t);
private:
	ActionState _currentStates;
	bool changeState(ActionState state);
	Action *_chickenRunAction;
	Action *_chickenStayAction;
	Action *_chickenFlyAction;
	static Chicken* _shareChicken;
};