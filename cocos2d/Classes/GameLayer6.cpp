#include "GameLayer6.h"

GameLayer6::GameLayer6(){
	_gameStatus = GAME_STATUS_START;
	_needScore = 10;
	_life = CHICKEN_LIFE;
	_speedStatus = true;
	_isInvicible = false;
}

GameLayer6::~GameLayer6(){}

void GameLayer6::onEnter()
{
	Layer::onEnter();
	this->_response = (int)UserDefault::getInstance()->getFloatForKey("response", 60);
	setAccelerometerEnabled(true);
	//log("response=%f", _response);
}

void GameLayer6::onExitTransitionDidStart()
{
	setAccelerometerEnabled(false);
}

bool GameLayer6::init(){
	if (!Layer::init()) {
		return false;
	}
	//get the origin point of the X-Y axis, and the visiable size of the screen
	_visiableSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();
	addParticle();

	// Add the chicken
	this->_chicken = Chicken::getInstance();
	this->_chicken->setPosition(_origin.x + _visiableSize.width - 50, _origin.y + 100);
	this->_chicken->getPhysicsBody()->setVelocity(Vect(0, 0));
	_yLast = _chicken->getPositionY();
	_chicken->setTag(1);
	_isInvicible = true;
	this->getChildByTag(4)->setVisible(true);
	scheduleOnce(schedule_selector(GameLayer6::chickenNotInvicible), 6);
	this->addChild(_chicken);

	//Add bird
	addBird();
	//Add world
	addWorld();
	//1.注册监听事件对象
	auto listener = EventListenerTouchOneByOne::create();      //多点触摸

	//2.定义监听对象的回调方法
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer6::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer6::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer6::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameLayer6::onTouchCancelled, this);

	//3.在事件监听器中注册（事件监听器包含：触摸事件、键盘相应事件、加速记录事件、鼠标响应事件、自定义事件）
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	/* 碰撞监听 */
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer6::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameLayer6::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//重力感应为真
	setAccelerometerEnabled(true);
	//随机
	srand((unsigned)time(NULL));

	scheduleUpdate();
	return true;
}

void GameLayer6::update(float delta){
	//检查是否跑到屏幕外
	getbackToScreen();
	//控制鸟移动
	chickenMoveControl();
}

//触摸开始时调用
bool GameLayer6::onTouchBegan(Touch* touch, Event* event)
{
	if (_gameStatus == GAME_STATUS_START)
	{
		SimpleAudioEngine::getInstance()->playEffect("sounds/whenFly.wav");
		this->_chicken->getPhysicsBody()->setVelocity(Vect(_chicken->getPhysicsBody()->getVelocity().x, 150));
		this->_chicken->chickenFly(true);
	}
	return true;
}

void GameLayer6::getbackToScreen()
{
	if (this->_chicken->getPositionX() < -15)
	{
		this->_chicken->setPositionX(_visiableSize.width + 15);
	}
	else if (this->_chicken->getPositionX() > _visiableSize.width + 15)
	{
		this->_chicken->setPositionX(-15);
	}

	for (auto bird : _birds)
	{
		if (bird->getPositionX() < -15)
		{
			bird->setPositionX(_visiableSize.width + 15);
		}
		else if (bird->getPositionX() > _visiableSize.width + 15)
		{
			bird->setPositionX(-15);
		}
	}

	for (auto egg : _eggs)
	{
		if (egg->getPositionX() < -2)
		{
			egg->setPositionX(_visiableSize.width + 2);
		}
		else if (egg->getPositionX() > _visiableSize.width + 2)
		{
			egg->setPositionX(-2);
		}
	}
}

void GameLayer6::chickenMoveControl()
{
	float x = _chicken->getPhysicsBody()->getVelocity().x;
	float y = _chicken->getPhysicsBody()->getVelocity().y;

	if (y > -2 && y < 2 && _yLast> -2 && _yLast < 2){
		if (x == _xLast && x == 0)
			this->_chicken->chickenStay();
		else
			_chicken->chickenRun();
	}
	else
	{
		_chicken->chickenFly();
	}

	_xLast = x;
	_yLast = y;
	getChildByTag(4)->setPosition(_chicken->getPosition());
}

//碰撞检测
bool GameLayer6::onContactBegin(PhysicsContact& contact){
	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (nodeA == NULL || nodeB == NULL)
	{
		return true;
	}
	Node* chickenNode = NULL;
	Node* eggNode = NULL;
	if (nodeB->getTag() == 1 && nodeA->getTag() == 3)
	{
		chickenNode = nodeB;
		eggNode = nodeA;
	}
	else if (nodeB->getTag() == 3 && nodeA->getTag() == 1)
	{
		chickenNode = nodeA;
		eggNode = nodeB;
	}
	else
	{
		/* 如果两个碰撞的物体中，不存在玩家对象，就忽略，不做处理 */
		return true;
	}
	for (int i = 0; i < _eggs.size(); i++) {
		auto egg = _eggs.at(i);
		if (egg == eggNode) {
			SimpleAudioEngine::getInstance()->playEffect("sounds/whenGetEgg.wav");
			egg->removeFromParentAndCleanup(true);
			_eggs.erase(i);
			eggSurprise();
			break;
		}
	}
	return true;
}
//碰撞检测
void GameLayer6::onContactSeparate(PhysicsContact& contact){
	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (nodeA == NULL || nodeB == NULL)
	{
		return;
	}

	Node* chickenNode = NULL;
	Node* birdNode = NULL;

	if (nodeA->getTag() == 1 && nodeB->getTag() == 2)
	{
		chickenNode = nodeA;
		birdNode = nodeB;
	}
	else if (nodeB->getTag() == 1 && nodeA->getTag() == 2)
	{
		chickenNode = nodeB;
		birdNode = nodeA;
	}
	else
	{
		/* 如果两个碰撞的物体中，不存在玩家对象，就忽略，不做处理 */
		return;
	}

	if (chickenNode->getPositionY() - birdNode->getPositionY() > 0)//打赢
	{
		for (int i = 0; i < _birds.size(); i++)
		{
			auto enemyT = _birds.at(i);
			if (enemyT == birdNode) {
				deathBond(birdNode->getPosition());
				int surprise = rand() % (int)(5);
				//eggSurprise();
				if (_eggs.size() < 2 && surprise == 3)
				{
					auto egg = Egg::create();
					egg->setPosition(birdNode->getPosition());
					egg->getPhysicsBody()->setVelocity(birdNode->getPhysicsBody()->getVelocity());
					_eggs.pushBack(egg);
					this->addChild(egg, -1, 3);
				}
				//加分
				_needScore--;
				this->delegator->onGamePlaying(_needScore);
				enemyT->removeFromParentAndCleanup(true);
				_birds.erase(i);
				SimpleAudioEngine::getInstance()->playEffect("sounds/whenWin.wav");
				schedule(schedule_selector(GameLayer6::addABird), 3, 3, 3);
				if (_needScore <= 0 && _gameStatus == GAME_STATUS_START)
				{
					_gameStatus = GAME_STARUS_WIN;
					gameWin();
				}
				return;
			}
		}
	}
	else if (chickenNode->getPositionY() - birdNode->getPositionY() < 0)//打输
	{
		if (_isInvicible == false)
		{
			deathBond(_chicken->getPosition());
			_chicken->getPhysicsBody()->setVelocity(Vect(0, 0));
			_chicken->setPosition(_origin.x + _visiableSize.width / 2, -50);
			_life--;
			if (_life > 0)
			{
				SimpleAudioEngine::getInstance()->playEffect("sounds/whenLose.wav");
				_gameStatus = GAME_STATUS_STAY;
				scheduleOnce(schedule_selector(GameLayer6::chickenRebirth), 3);
				this->delegator->showLifes(_life);
			}
			else
			{
				//失败逻辑
				SimpleAudioEngine::getInstance()->playEffect("sounds/whenGameOver.wav");
				_gameStatus = GAME_STATUS_OVER;
				this->delegator->showLifes(_life);
				removeChild(_chicken);
				gameOver();
				/*auto scene = WelcomeScene::create();
				TransitionScene *transition = TransitionFade::create(1, scene);
				Director::getInstance()->replaceScene(transition);*/
			}
		}
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect("sounds/whenHit.wav");
}

void GameLayer6::onAcceleration(Acceleration* acc, Event* event){
	if (_chicken == nullptr){
		return;
	}

	if (_chicken->getActionState() == STATE_FLY)
	{
		if (_chicken->getPhysicsBody()->getVelocity().x > 150){
			if (acc->x < 0){
				_chicken->getPhysicsBody()->setVelocity(Vect(_chicken->getPhysicsBody()->getVelocity().x + acc->x * _response,
					_chicken->getPhysicsBody()->getVelocity().y));
			}
		}
		else if (_chicken->getPhysicsBody()->getVelocity().x < -150){
			if (acc->x > 0){
				_chicken->getPhysicsBody()->setVelocity(Vect(_chicken->getPhysicsBody()->getVelocity().x + acc->x * _response,
					_chicken->getPhysicsBody()->getVelocity().y));
			}
		}
		else
			_chicken->getPhysicsBody()->setVelocity(Vect(_chicken->getPhysicsBody()->getVelocity().x + acc->x * _response,
			_chicken->getPhysicsBody()->getVelocity().y));
	}
	else
	{
		if (_chicken->getPhysicsBody()->getVelocity().x > 100){
			if (acc->x < -0.1){
				_chicken->getPhysicsBody()->setVelocity(Vect(_chicken->getPhysicsBody()->getVelocity().x - 30,
					_chicken->getPhysicsBody()->getVelocity().y));
			}
		}
		else if (_chicken->getPhysicsBody()->getVelocity().x < -100){
			if (acc->x > 0.1){
				_chicken->getPhysicsBody()->setVelocity(Vect(_chicken->getPhysicsBody()->getVelocity().x + 30,
					_chicken->getPhysicsBody()->getVelocity().y));
			}
		}
		else
		{
			if (acc->x < -0.1)
				_chicken->getPhysicsBody()->setVelocity(Vect(_chicken->getPhysicsBody()->getVelocity().x - 30,
				_chicken->getPhysicsBody()->getVelocity().y));
			else if (acc->x >0.1)
				_chicken->getPhysicsBody()->setVelocity(Vect(_chicken->getPhysicsBody()->getVelocity().x + 30,
				_chicken->getPhysicsBody()->getVelocity().y));
		}
	}
	//方向
	if (acc->x > 0.05)
	{
		_chicken->setFlippedX(true);
	}
	else if (acc->x < -0.05)
	{
		_chicken->setFlippedX(false);
	}
}

void GameLayer6::eggSurprise()
{
	int surprise = rand() % (int)(3);
	switch (surprise)
		//switch (0)
	{
	case 0:
		_speedStatus = false;
		scheduleOnce(schedule_selector(GameLayer6::getBackBirdSpeed), 10);
		break;
	case 1:
		_isInvicible = true;
		this->getChildByTag(4)->setVisible(true);
		scheduleOnce(schedule_selector(GameLayer6::chickenNotInvicible), 10);
		break;
	case 2:
		if (_life <= 2)
		{
			_life++;
			this->delegator->showLifes(_life);
		}
	}
}

void GameLayer6::getBackBirdSpeed(float dt)
{
	_speedStatus = true;
}

void GameLayer6::chickenNotInvicible(float dt)
{
	_isInvicible = false;
	this->getChildByTag(4)->setVisible(false);
}

void GameLayer6::addParticle()
{
	auto parSnow = ParticleSnow::createWithTotalParticles(100);
	parSnow->setVisible(true);
	parSnow->setPosition(_origin.x + _visiableSize.width * 1 / 2, _origin.y + _visiableSize.height);
	addChild(parSnow, 0, 10);
	///////////
	//auto a = ParticleSystemQuad::create();

	//a = ParticleFireworks::createWithTotalParticles(5);
	//
	//a->setPosition(origin.x + visiableSize.width * 1 / 2, 0);
	////a->setScale(2);
	//addChild(a);
	//removeChildByTag(5);

	//护盾粒子效果
	auto defend = Sprite::create();
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.2);
	animation->addSpriteFrameWithFileName("image/defend1.png");
	animation->addSpriteFrameWithFileName("image/defend2.png");
	Animate* animate = Animate::create(animation);
	auto chickenRunAction = RepeatForever::create(animate);
	defend->runAction(chickenRunAction);
	defend->setScale(0.7);

	//auto particle = ParticleSun::createWithTotalParticles(30);
	defend->setPosition(_origin.x + _visiableSize.width * 1 / 2, _origin.y + _visiableSize.height / 2);
	defend->setVisible(false);
	addChild(defend, -1, 4);
}

void GameLayer6::deathBond(Point point)
{
	auto dBond = Sprite::create();
	dBond->setPosition(point);
	this->addChild(dBond, 0, 20);
	Animation *bondAnimation = Animation::create();
	bondAnimation->setDelayPerUnit(0.2);
	bondAnimation->addSpriteFrameWithFileName("image/3.png");
	bondAnimation->addSpriteFrameWithFileName("image/2.png");
	bondAnimation->addSpriteFrameWithFileName("image/1.png");
	Animate* animate = Animate::create(bondAnimation);
	CallFunc *actionDone = CallFunc::create(bind(&GameLayer6::removeDBond, this));
	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
	dBond->runAction(sequence);
}

void GameLayer6::removeDBond()
{
	this->removeChildByTag(20);
}

void GameLayer6::addWorld()
{
	// Add the ground-down
	auto groundNode = Sprite::create("image/earth.png");
	float landHeight = 102;
	auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(350, groundNode->getContentSize().height - 10)));
	groundBody->setDynamic(false);
	groundBody->getShape(0)->setRestitution(0.0f);
	groundBody->getShape(0)->setFriction(0.1);
	groundNode->setPhysicsBody(groundBody);
	groundNode->setPosition(_origin.x + _visiableSize.width / 2, _origin.y + _visiableSize.height / 2 - 240 + groundNode->getContentSize().height / 2);
	addChild(groundNode);

	// Add the ground-up
	auto skyNode = Node::create();
	auto skyBody = PhysicsBody::create();
	skyBody->addShape(PhysicsShapeBox::create(Size(350, 50)));
	skyBody->setDynamic(false);
	skyBody->getShape(0)->setRestitution(0.5f);
	skyBody->getShape(0)->setFriction(0);
	skyNode->setPhysicsBody(skyBody);
	skyNode->setPosition(_origin.x + _visiableSize.width / 2, _origin.y + _visiableSize.height / 2 + 225);
	this->addChild(skyNode);

	// Add the cloud
	for (int i = 2; i <= 4; i++)
	{
		Sprite *cloud;
		if (i % 2 == 0)
		{
			cloud = Sprite::create("image/cloud1.png");
		}
		else
		{
			cloud = Sprite::create("image/cloud2.png");
		}
		auto cloudBody = PhysicsBody::create();
		cloudBody->addShape(PhysicsShapeBox::create(Size(cloud->getContentSize().width - 5, 15)));
		cloudBody->setDynamic(false);
		cloudBody->getShape(0)->setRestitution(0.0f);
		cloudBody->getShape(0)->setFriction(0.1);
		cloud->setPhysicsBody(cloudBody);
		if (i == 2)
			cloud->setPosition(_origin.x + 15, _origin.y + _visiableSize.height / 2);
		else if (i == 3)
			cloud->setPosition(_origin.x + _visiableSize.width / 2, _origin.y + _visiableSize.height / 2 + 110);
		else if (i == 4)
			cloud->setPosition(_origin.x + _visiableSize.width - 15, _origin.y + _visiableSize.height / 2);
		this->addChild(cloud, 5);
	}
}

void GameLayer6::chickenRebirth(float dt)
{
	_isInvicible = true;
	this->getChildByTag(4)->setVisible(true);

	_chicken->getPhysicsBody()->setVelocity(Vect(0, 0));
	scheduleOnce(schedule_selector(GameLayer6::chickenNotInvicible), 6);

	int i = rand() % (int)(3) + 2;
	if (i == 2)
		_chicken->setPosition(_origin.x + 15, _origin.y + _visiableSize.height / 2 + 5);
	else if (i == 3)
		_chicken->setPosition(_origin.x + _visiableSize.width / 2, _origin.y + _visiableSize.height / 2 + 115);
	else if (i == 4)
		_chicken->setPosition(_origin.x + _visiableSize.width - 15, _origin.y + _visiableSize.height / 2 + 5);
	_gameStatus = GAME_STATUS_START;
}

void GameLayer6::addABird(float dt)
{
	if (_birds.size() < 3)
	{
		Sprite *bird;
		int i = rand() % (int)(10) + 1;
		if (i >= 1 && i <= 5)
		{
			bird = NormalBird::create();
		}
		else if (i >= 6 && i <= 8)
		{
			bird = RedBird::create();
		}
		else if (i == 9 || i == 10)
		{
			bird = BlueBird::create();
		}
		i = rand() % (int)(3) + 2;
		if (i == 2)
			bird->setPosition(_origin.x + 15, _origin.y + _visiableSize.height / 2 + 5);
		else if (i == 3)
			bird->setPosition(_origin.x + _visiableSize.width / 2, _origin.y + _visiableSize.height / 2 + 115);
		else if (i==4)
			bird->setPosition(_origin.x + _visiableSize.width - 15, _origin.y + _visiableSize.height / 2 + 5);
		//bird->yLast = bird->getPositionY();
		bird->setTag(2);
		this->_birds.pushBack(bird);
		this->addChild(bird, -2);
	}
}

void GameLayer6::addBird()
{
	for (int i = 2; i <= 4; i++)
	{
		Sprite *bird;
		if (i % 2 == 0)
		{
			bird = NormalBird::create();
		}
		else
			bird = BlueBird::create();

		if (i == 2)
			bird->setPosition(_origin.x + 15, _origin.y + _visiableSize.height / 2 + 5);
		else if (i == 3)
			bird->setPosition(_origin.x + _visiableSize.width / 2, _origin.y + _visiableSize.height / 2 + 115);
		else if (i == 4)
			bird->setPosition(_origin.x + _visiableSize.width - 15, _origin.y + _visiableSize.height / 2 + 5);
		bird->setTag(2);
		this->_birds.pushBack(bird);
		this->addChild(bird);
	}
}

void GameLayer6::gameOver()
{
	this->delegator->onGameEnd(this->_needScore);
	_gameStatus = GAME_STATUS_OVER;
	setAccelerometerEnabled(false);
}

void GameLayer6::gameWin()
{
	_eventDispatcher->removeEventListenersForType(EventListener::Type::ACCELERATION);
	//_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	removeChild(_chicken);
	this->delegator->onGameWin();
	setAccelerometerEnabled(false);
}

void GameLayer6::showScore()
{
	this->delegator->onGamePlaying(_needScore);
}