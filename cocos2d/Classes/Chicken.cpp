#include "Chicken.h"

Chicken::Chicken() {
}

Chicken::~Chicken() {
}

Chicken* Chicken::_shareChicken = nullptr;

Chicken* Chicken::getInstance(){
	if (_shareChicken == NULL){
		_shareChicken = new Chicken();
		if (!_shareChicken->init()){
			delete(_shareChicken);
			_shareChicken = NULL;
		}
	}
	return _shareChicken;
}

bool Chicken::init() {
	if (!Sprite::init()){
		return false;
	}
	_shareChicken->initWithFile("image/Chicken.png");
	//add physics body
	this->setScale(0.25);
	PhysicsBody *ChickenBody = PhysicsBody::create(10);
	ChickenBody->addShape(PhysicsShapeBox::create(Size(40, 50)));
	ChickenBody->setCategoryBitmask(1);
	ChickenBody->setCollisionBitmask(1);
	ChickenBody->setContactTestBitmask(1);
	ChickenBody->setDynamic(true);
	ChickenBody->setLinearDamping(0.5f);
	//设置弹性
	ChickenBody->getShape(0)->setRestitution(1.0f);
	ChickenBody->getShape(0)->setFriction(5);
	//不能旋转
	ChickenBody->setRotationEnable(false);
	this->setPhysicsBody(ChickenBody);

	//schedule(schedule_selector(Chicken::MyUpdate, this), 1);
	return true;
}

Animate* Chicken::createAnimate(ActionState tobeState) {
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.2);
	/*Rect rect = Rect(0, 0,85, 120);
	auto spriteFrame = SpriteFrame::create("image/Chicken1.png", rect);*/
	switch (tobeState)
	{
	case STATE_RUN:
		//animation->addSpriteFrame(spriteFrame);
		animation->addSpriteFrameWithFileName("image/Chickenrun_1.png");
		animation->addSpriteFrameWithFileName("image/Chickenrun_2.png");
		animation->addSpriteFrameWithFileName("image/Chickenrun_3.png");
		animation->addSpriteFrameWithFileName("image/Chickenrun_4.png");
		break;
	case STATE_STAY:
		animation->addSpriteFrameWithFileName("image/Chickenstay.png");
		break;
	case STATE_FLY:
		animation->addSpriteFrameWithFileName("image/Chickenfly_1.png");
		animation->addSpriteFrameWithFileName("image/Chickenfly_2.png");
		break;
	}
	Animate* animate = Animate::create(animation);
	return animate;
}

void Chicken::chickenRun(){
	if (changeState(STATE_RUN))
	{
		auto *animateRun = createAnimate(STATE_RUN);
		this->_chickenRunAction = RepeatForever::create(animateRun);
		this->stopAllActions();
		this->runAction(_chickenRunAction);
	}
}

void Chicken::chickenStay(){
	if (changeState(STATE_STAY))
	{
		auto *animateStay = createAnimate(STATE_STAY);
		this->_chickenStayAction = RepeatForever::create(animateStay);
		this->stopAllActions();
		this->runAction(_chickenStayAction);
	}
}

void Chicken::chickenFly(bool isouch){
		auto *animateFly = createAnimate(STATE_FLY);
		this->stopAllActions();
		this->runAction(animateFly);
		_currentStates = STATE_FLY;
}

void Chicken::chickenFly(){
	if (changeState(STATE_FLY))
	{
		auto *animateFly = createAnimate(STATE_FLY);
		this->stopAllActions();
		this->runAction(animateFly);
	}
	
}

bool Chicken::changeState(ActionState state) {
	if (_currentStates == state)
	{
		return false;
	}
	_currentStates = state;
	return true;
}

ActionState Chicken::getActionState(){
	return _currentStates;
}

//void Chicken::MyUpdate(float t)
//{
//	log("niiiiiiii");
//}