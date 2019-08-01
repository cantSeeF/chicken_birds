#include "Eagle.h"

Eagle::Eagle() {
	_speed = 70;
}

Eagle::~Eagle() {
}

bool Eagle::init() {
	if (!Sprite::init()){
		return false;
	}
	_visiableSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

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
	this->_isFirstTime = 3;
	this->setColor(Color3B::ORANGE);
	this->birdFly();
	scheduleUpdate();
	return true;
}

Animate* Eagle::createAnimate(ActionState tobeState) {
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

void Eagle::birdFly(){
	if (changeState(STATE_FLY))
	{
		auto *animateFly = createAnimate(STATE_FLY);
		this->_birdFlyAction = RepeatForever::create(animateFly);
		this->stopAllActions();
		this->runAction(_birdFlyAction);
	}
}

bool Eagle::changeState(ActionState state) {
	if (_currentStatus == state)
	{
		return false;
	}
	_currentStatus = state;
	return true;
}

int Eagle::getSpeed()
{
	return _speed;
}

void Eagle::update(float t)
{
	if (this->getPositionX() < _origin.x + 20)
	{
		_speed = 70;
		this->setFlippedX(false);
	}
	else if (this->getPositionX() > _origin.x + _visiableSize.width - 20)
	{
		_speed = -70;
		this->setFlippedX(true);
	}
	this->getPhysicsBody()->setVelocity(Vect(this->getSpeed(), 0));
	this->setPositionY(_origin.y + _visiableSize.height / 2 + 195);
}