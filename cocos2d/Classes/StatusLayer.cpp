#include"StatusLayer.h"
#include"GameScene.h"
#include"WelcomeScene.h"

bool StatusLayer::init(){
	if (!Layer::init()) {
		return false;
	}
	this->_currentScore = 0;

	this->_visibleSize = Director::getInstance()->getVisibleSize();
	this->_origin = Director::getInstance()->getVisibleOrigin();

	auto scoreSprite = LabelBMFont::create("0", "fonts/futura-48.fnt");
	//scoreSprite->setVisible(true);
	scoreSprite->setScale(0.5);
	this->addChild(scoreSprite);
	scoreSprite->setTag(100);
	//score->setString("0");
	scoreSprite->setPosition(_origin.x + _visibleSize.width - 15, _origin.y + _visibleSize.height / 2 + 210);

	//暂停机制
	MenuItemImage *pCloseItem = MenuItemImage::create("image/CloseSelected.png","image/CloseNormal.png",
		CC_CALLBACK_1(StatusLayer::menuPauseCallback, this));
	pCloseItem->setPosition(Point(_origin.x + 15, _origin.y + _visibleSize.height / 2 + 210));
	auto *pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(_origin.x,_origin.y);
	addChild(pMenu);

	for (int i = 0; i < 3; i++)
	{
		auto egg = Sprite::create("image/egg-life.png");
		egg->setScale(0.6);
		egg->setPosition(40 + i * 15, _origin.y + _visibleSize.height / 2 + 210);
		_eggLife.pushBack(egg);
		addChild(egg);
	}
	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	//和回调函数绑定
	listener->onKeyReleased = CC_CALLBACK_2(StatusLayer::onKeyReleased, this);
	//添加到事件分发器中
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void StatusLayer::onGamePlaying(int score){
	_currentScore = score;
	auto scoreSprite = (LabelBMFont*)this->getChildByTag(100);
	String* s = String::createWithFormat("%d", score);
	scoreSprite->setString(s->getCString());
}

//返回键
void StatusLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	RenderTexture *renderTexture = RenderTexture::create(_visibleSize.width, _visibleSize.height);
	//遍历当前类的所有子节点信息，画入renderTexture中。  
	//这里类似截图。  
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面  
	Director::sharedDirector()->pushScene(GamePause::scene(renderTexture));
}

void StatusLayer::showLifes(int life)
{
	for (int i = 0; i < 3; i++)
	{
		auto egg = _eggLife.at(i);
		if (i < life)
		{
			egg->setVisible(true);
		}
		else
		{
			egg->setVisible(false);
		}
	}
}

void StatusLayer::onGameEnd(int curScore)
{
	this->_currentScore = curScore;
	fadeInGameOver();
}

void StatusLayer::onGameWin()
{
	// create the game over panel
	Sprite* gameWinSprite = Sprite::create("image/head.png");
	gameWinSprite->setPosition(Point(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2 + 130));
	this->addChild(gameWinSprite);
	auto gameoverFadeIn = FadeIn::create(0.5f);

	// Start next action
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
	auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
	gameWinSprite->stopAllActions();
	gameWinSprite->runAction(sequence);
}

void StatusLayer::fadeInGameOver(){
	// create the game over panel
	Sprite* gameOverSprite = Sprite::create("image/gameover.png");
	gameOverSprite->setPosition(Point(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2 + 145));
	this->addChild(gameOverSprite);
	auto gameoverFadeIn = FadeIn::create(0.5f);

	// Start next action
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
	auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
	gameOverSprite->stopAllActions();
	gameOverSprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel(){
	//current score;
	String *s = String::createWithFormat("%d", _currentScore);
	auto curScoreSprite = LabelBMFont::create("0", "fonts/futura-48.fnt");
	curScoreSprite->setString(s->getCString());
	curScoreSprite->setScale(0.5);
	curScoreSprite->setPosition(_origin.x + _visibleSize.width / 2 - 50 , _origin.y + _visibleSize.height / 2 );
	addChild(curScoreSprite);

	// Start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f, Point(_origin.x + _visibleSize.width / 2,_origin.y + _visibleSize.height / 2 + 10));
	// add variable motion for the action
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
	auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
	curScoreSprite->stopAllActions();
	curScoreSprite->runAction(sequence);
}

void StatusLayer::fadeInRestartBtn(){
	Node * tmpNode = Node::create();
	Sprite* nextLevelBtn = Sprite::create("image/back.png");
	nextLevelBtn->setFlippedX(true);
	//注意区分是不是最后一关
	int level = 1 + UserDefault::getInstance()->getIntegerForKey("levelSelect");
	__String *s = __String::createWithFormat("isLevel%dLock", level);
	UserDefault::getInstance()->setBoolForKey(s->getCString(), false);
	MenuItemSprite* nextLevel;
	nextLevel =MenuItemSprite::create(nextLevelBtn, nextLevelBtn, NULL, CC_CALLBACK_1(StatusLayer::menuNextLevelCallback, this));
	nextLevel->setPosition(_origin.x + _visibleSize.width / 2 + 50, _origin.y + _visibleSize.height / 2 - 100);
	//create the restart menu;
	Sprite* restartBtn = Sprite::create("image/replay.png");
	Sprite* restartBtnActive = Sprite::create("image/replay.png");
	restartBtnActive->setPositionY(-4);
	auto  restartItem = MenuItemSprite::create(restartBtn, restartBtnActive, NULL, CC_CALLBACK_1(StatusLayer::menuRestartCallback, this));
	restartItem->setPosition(_origin.x + _visibleSize.width / 2 - 50, _origin.y + _visibleSize.height / 2 - 100);

	auto menu = Menu::create(restartItem, nextLevel, NULL);
	menu->setPosition(_origin.x, _origin.y);
	tmpNode->addChild(menu);

	//create the rate button. however ,this button is not available yet = =
	this->addChild(tmpNode);

	//fade in the two buttons
	auto fadeIn = FadeIn::create(0.1f);
	//tmpNode->stopAllActions();
	//tmpNode->runAction(fadeIn);
	tmpNode->stopAllActions();
	tmpNode->runAction(fadeIn);
}

void StatusLayer::menuRestartCallback(Ref* pSender){
	//UserDefault::getInstance()->setIntegerForKey("levelSelect", 1);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

//以下是暂停部分
void StatusLayer::menuPauseCallback(Ref* pSender)
{
	RenderTexture *renderTexture = RenderTexture::create(_visibleSize.width, _visibleSize.height);
	//遍历当前类的所有子节点信息，画入renderTexture中。  
	//这里类似截图。  
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面  
	Director::sharedDirector()->pushScene(GamePause::scene(renderTexture));
}

void StatusLayer::menuNextLevelCallback(Ref* pSender)
{
	int level = UserDefault::getInstance()->getIntegerForKey("levelSelect");
	if (level <= 8)
	{
		level++;
	}
	else
		return;
	UserDefault::getInstance()->setIntegerForKey("levelSelect",level);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}