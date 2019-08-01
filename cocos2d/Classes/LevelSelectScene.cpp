#include "WelcomeScene.h"

LevelSelectScene::LevelSelectScene(){};

LevelSelectScene::~LevelSelectScene(){};

bool LevelSelectScene::init(){
	if (!Scene::init())
	{
		return false;
	}
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//背景
	auto background = Sprite::create("image/00.png");
	background->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2);
	this->addChild(background);

	//设置关锁
	UserDefault::getInstance()->setBoolForKey("isLevel1Lock", false);
	UserDefault::getInstance()->setBoolForKey("isLevel2Lock", false);
	UserDefault::getInstance()->setBoolForKey("isLevel3Lock", false);
	UserDefault::getInstance()->setBoolForKey("isLevel4Lock", false);
	UserDefault::getInstance()->setBoolForKey("isLevel5Lock", false);
	UserDefault::getInstance()->setBoolForKey("isLevel6Lock", false);
	UserDefault::getInstance()->setBoolForKey("isLevel7Lock", false);
	UserDefault::getInstance()->setBoolForKey("isLevel8Lock", false);
	UserDefault::getInstance()->setBoolForKey("isLevel9Lock", false);
	//int level = 10;
	//__String *s = __String::createWithFormat("ssss%d", level);
	////log("%s", s->getCString());
	//UserDefault::getInstance()->setIntegerForKey(s->getCString(), 1234);
	//log("+++++++++%d",UserDefault::getInstance()->getIntegerForKey("ssss10"));

	auto menu = Menu::create();
	//第一关
	MenuItemSprite *level1Item;
	Sprite *level1;
	if (! UserDefault::getInstance()->getBoolForKey("isLevel1Lock"))
	{
		level1 = Sprite::create("image/key.png");
		auto level1_1 = Sprite::create("image/key.png");
		level1_1->setScale(1.1);
		level1Item = MenuItemSprite::create(level1, level1_1, CC_CALLBACK_1(LevelSelectScene::menuLevel1Callback, this));
		level1Item->setPosition(origin.x + visiableSize.width / 2 - 80, origin.y + visiableSize.height / 2 + 120);
		menu->addChild(level1Item);
	}
	else
	{
		level1 = Sprite::create("image/lock.png");
		level1->setPosition(origin.x + visiableSize.width / 2 - 80, origin.y + visiableSize.height / 2 + 120);
		addChild(level1);
	}
	// 第二关
	MenuItemSprite *level2Item;
	Sprite *level2;
	if (!UserDefault::getInstance()->getBoolForKey("isLevel2Lock",true))
	{
		level2 = Sprite::create("image/key.png");
		auto level2_1 = Sprite::create("image/key.png");
		level2_1->setScale(1.1);
		level2Item = MenuItemSprite::create(level2, level2_1, CC_CALLBACK_1(LevelSelectScene::menuLevel2Callback, this));
		level2Item->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 + 120);
		menu->addChild(level2Item);
	}
	else
	{
		level2 = Sprite::create("image/lock.png");
		level2->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 + 120);
		addChild(level2);
	}
	// 第三关
	MenuItemSprite *level3Item;
	Sprite *level3;
	if (!UserDefault::getInstance()->getBoolForKey("isLevel3Lock",true))
	{
		level3 = Sprite::create("image/key.png");
		auto level3_1 = Sprite::create("image/key.png");
		level3_1->setScale(1.1);
		level3Item = MenuItemSprite::create(level3, level3_1, CC_CALLBACK_1(LevelSelectScene::menuLevel3Callback, this));
		level3Item->setPosition(origin.x + visiableSize.width / 2 + 80, origin.y + visiableSize.height / 2 + 120);
		menu->addChild(level3Item);
	}
	else
	{
		level3 = Sprite::create("image/lock.png");
		level3->setPosition(origin.x + visiableSize.width / 2 + 80, origin.y + visiableSize.height / 2 + 120);
		addChild(level3);
	}
	// 第四关
	MenuItemSprite *level4Item;
	Sprite *level4;
	if (!UserDefault::getInstance()->getBoolForKey("isLevel4Lock",true))
	{
		level4 = Sprite::create("image/key.png");
		auto level4_1 = Sprite::create("image/key.png");
		level4_1->setScale(1.1);
		level4Item = MenuItemSprite::create(level4, level4_1, CC_CALLBACK_1(LevelSelectScene::menuLevel4Callback, this));
		level4Item->setPosition(origin.x + visiableSize.width / 2 - 80, origin.y + visiableSize.height / 2 + 20);
		menu->addChild(level4Item);
	}
	else
	{
		level4 = Sprite::create("image/lock.png");
		level4->setPosition(origin.x + visiableSize.width / 2 - 80, origin.y + visiableSize.height / 2 + 20);
		addChild(level4);
	}
	// 第五关
	MenuItemSprite *level5Item;
	Sprite *level5;
	if (!UserDefault::getInstance()->getBoolForKey("isLevel5Lock",true))
	{
		level5 = Sprite::create("image/key.png");
		auto level5_1 = Sprite::create("image/key.png");
		level5_1->setScale(1.1);
		level5Item = MenuItemSprite::create(level5, level5_1, CC_CALLBACK_1(LevelSelectScene::menuLevel5Callback, this));
		level5Item->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 + 20);
		menu->addChild(level5Item);
	}
	else
	{
		level5 = Sprite::create("image/lock.png");
		level5->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 + 20);
		addChild(level5);
	}
	// 第六关
	MenuItemSprite *level6Item;
	Sprite *level6;
	if (!UserDefault::getInstance()->getBoolForKey("isLevel6Lock",true))
	{
		level6 = Sprite::create("image/key.png");
		auto level6_1 = Sprite::create("image/key.png");
		level6_1->setScale(1.1);
		level6Item = MenuItemSprite::create(level6, level6_1, CC_CALLBACK_1(LevelSelectScene::menuLevel6Callback, this));
		level6Item->setPosition(origin.x + visiableSize.width / 2 + 80, origin.y + visiableSize.height / 2 + 20);
		menu->addChild(level6Item);
	}
	else
	{
		level6 = Sprite::create("image/lock.png");
		level6->setPosition(origin.x + visiableSize.width / 2 + 80, origin.y + visiableSize.height / 2 + 20);
		addChild(level6);
	}

	// 第七关
	MenuItemSprite *level7Item;
	Sprite *level7;
	if (!UserDefault::getInstance()->getBoolForKey("isLevel7Lock",true))
	{
		level7 = Sprite::create("image/key.png");
		auto level7_1 = Sprite::create("image/key.png");
		level7_1->setScale(1.1);
		level7Item = MenuItemSprite::create(level7, level7_1, CC_CALLBACK_1(LevelSelectScene::menuLevel7Callback, this));
		level7Item->setPosition(origin.x + visiableSize.width / 2 - 80, origin.y + visiableSize.height / 2 - 80);
		menu->addChild(level7Item);
	}
	else
	{
		level7 = Sprite::create("image/lock.png");
		level7->setPosition(origin.x + visiableSize.width / 2 - 80, origin.y + visiableSize.height / 2 - 80);
		addChild(level7);
	}
	// 第八关
	MenuItemSprite *level8Item;
	Sprite *level8;
	if (!UserDefault::getInstance()->getBoolForKey("isLevel8Lock",true))
	{
		level8 = Sprite::create("image/key.png");
		auto level8_1 = Sprite::create("image/key.png");
		level8_1->setScale(1.1);
		level8Item = MenuItemSprite::create(level8, level8_1, CC_CALLBACK_1(LevelSelectScene::menuLevel8Callback, this));
		level8Item->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 - 80);
		menu->addChild(level8Item);
	}
	else
	{
		level8 = Sprite::create("image/lock.png");
		level8->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 - 80);
		addChild(level8);
	}

	// 第九关
	MenuItemSprite *level9Item;
	Sprite *level9;
	if (!UserDefault::getInstance()->getBoolForKey("isLevel9Lock",true))
	{
		level9 = Sprite::create("image/key.png");
		auto level9_1 = Sprite::create("image/key.png");
		level9_1->setScale(1.1);
		level9Item = MenuItemSprite::create(level9, level9_1, CC_CALLBACK_1(LevelSelectScene::menuLevel9Callback, this));
		level9Item->setPosition(origin.x + visiableSize.width / 2 + 80, origin.y + visiableSize.height / 2 - 80);
		menu->addChild(level9Item);
	}
	else
	{
		level9 = Sprite::create("image/lock.png");
		level9->setPosition(origin.x + visiableSize.width / 2 + 80, origin.y + visiableSize.height / 2 - 80);
		addChild(level9);
	}

	menu->setPosition(origin.x, origin.y);
	this->addChild(menu);

	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(LevelSelectScene::onKeyReleased, this);
	//添加到事件分发器中
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void LevelSelectScene::menuLevel1Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 1);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(scene);
}

void LevelSelectScene::menuLevel2Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 2);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void LevelSelectScene::menuLevel3Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 3);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void LevelSelectScene::menuLevel4Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 4);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void LevelSelectScene::menuLevel5Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 5);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void LevelSelectScene::menuLevel6Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 6);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void LevelSelectScene::menuLevel7Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 7);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void LevelSelectScene::menuLevel8Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 8);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void LevelSelectScene::menuLevel9Callback(Object *sender)
{
	UserDefault::getInstance()->setIntegerForKey("levelSelect", 9);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

//返回键
void LevelSelectScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	auto scene = WelcomeScene::create();
	//TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(scene);
}