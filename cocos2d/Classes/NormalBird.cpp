#include "NormalBird.h"

NormalBird::NormalBird() {
	_speed = 50;
}

NormalBird::~NormalBird() {
}

bool NormalBird::init() {
	if (!Sprite::init()){
		return false;
	}
	this->initWithFile("image/bird.png");
	this->setScale(0.25);
	PhysicsBody *birdBody = PhysicsBody::create(10);
	birdBody->addShape(PhysicsShapeBox::create(Size(40, 50)));
	birdBody->setCategoryBitmask(1);
	birdBody->setCollisionBitmask(1);
	birdBody->setContactTestBitmask(1);
	birdBody->setDynamic(true);
	/**
	* 设置阻尼值
	*它用来模拟body在气体或者液体中的摩擦力
	*取值范围是 0.0f to 1.0f.*/
	birdBody->setLinearDamping(0.5f);
	//设置弹性
	birdBody->getShape(0)->setRestitution(0.5f);
	birdBody->getShape(0)->setFriction(1);
	//不能旋转
	birdBody->setRotationEnable(false);
	this->setPhysicsBody(birdBody);

	this->birdRun();
	this->_isFirstTime = 3;
	scheduleUpdate();
	return true;
}

Animate* NormalBird::createAnimate(ActionState tobeState) {
	Animation *animation = Animation::create();
	
	Rect rect = Rect(0, 0, 85, 120);
	auto spriteFrame = SpriteFrame::create("image/birdstay.png", rect);
	switch (tobeState)
	{
	case STATE_RUN:
		animation->setDelayPerUnit(0.3);
		//animation->addSpriteFrame(spriteFrame);
		//animation->addSpriteFrameWithFileName("image/bird_1.png");
		animation->addSpriteFrameWithFileName("image/birdRun1.png");
		animation->addSpriteFrameWithFileName("image/birdRun2.png");
		break;
	case STATE_FLY:
		animation->setDelayPerUnit(0.5);
		animation->addSpriteFrameWithFileName("image/birdFly1.png");
		animation->addSpriteFrameWithFileName("image/birdFly2.png");
		break;
	}
	Animate* animate = Animate::create(animation);
	return animate;
}

void NormalBird::birdRun(){
	if (changeState(STATE_RUN))
	{
		auto *animateRun = createAnimate(STATE_RUN);
		this->_birdRunAction = RepeatForever::create(animateRun);
		this->stopAllActions();
		this->runAction(_birdRunAction);
	}
}

void NormalBird::birdFly(){
	if (changeState(STATE_FLY))
	{
		auto *animateFly = createAnimate(STATE_FLY);
		this->_birdFlyAction = RepeatForever::create(animateFly);
		this->stopAllActions();
		this->runAction(_birdFlyAction);
	}
}

bool NormalBird::changeState(ActionState state) {
	if (_currentStatus == state)
	{
		return false;
	}
	_currentStatus = state;
	return true;
}

int NormalBird::getSpeed()
{
	return _speed;
}

void NormalBird::update(float t)
{
	float y = this->getPhysicsBody()->getVelocity().y;
	int direct = rand() % (int)(80);
	int fly = rand() % (int)(16);
	//设置速度
	if (direct == 1)
	{
		this->getPhysicsBody()->setVelocity(Vect(this->getSpeed(), this->getPhysicsBody()->getVelocity().y));
	}
	else if (direct == 2)
	{
		this->getPhysicsBody()->setVelocity(Vect(-this->getSpeed(), this->getPhysicsBody()->getVelocity().y));
	}
	//飞行
	if (fly == 1)
	{
		this->getPhysicsBody()->setVelocity(Vect(this->getPhysicsBody()->getVelocity().x, 115));
	}
	//状态
	if (y - this->yLast < -6 || y - this->yLast > 6){
		this->birdFly();
	}
	else if (y - this->yLast == 0)
	{
		this->birdRun();
	}
	//朝向
	if (this->getPhysicsBody()->getVelocity().x > 0)
	{
		this->setFlippedX(false);
	}
	else if (this->getPhysicsBody()->getVelocity().x < 0)
	{
		this->setFlippedX(true);
	}
	this->yLast = y;
}