#include "WelcomeScene.h"
//#include"platform\android\jni\JniHelper.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include"platform\android\jni\JniHelper.h"
#endif

WelcomeScene::WelcomeScene(){};

WelcomeScene::~WelcomeScene(){};

bool WelcomeScene::init(){
	if (!Scene::init())
	{
		return false;
	}
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	_isMusicOpen = true;

	auto background = Sprite::create("image/00.png");
	//background->setColor(cocos2d::ccRED);
	background->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2);
	this->addChild(background);

	auto earth = Sprite::create("image/earth.png");
	earth->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 - 240 + earth->getContentSize().height / 2);
	this->addChild(earth);

	auto killMuji = Sprite::create("image/killmuji.png");
	killMuji->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 + 150);
	this->addChild(killMuji);
	//开始按钮
	auto startButton = Sprite::create("image/button.png");
	auto startButton2 = Sprite::create("image/button.png");
	startButton2->setPositionY(-5);
	auto startItem = MenuItemSprite::create(startButton,startButton2, CC_CALLBACK_1(WelcomeScene::menuStartCallback, this));
	startItem->setPosition(Point(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2 + 50));

	//声音控制
	auto soundOpen = MenuItemImage::create("image/sound.png","image/sound.png");
	auto soundClose = MenuItemImage::create("image/sound2.png", "image/sound2.png");
	MenuItemToggle *soundsItem = MenuItemToggle::createWithTarget(this, SEL_MenuHandler(&WelcomeScene::menuMusicCallback), soundOpen, soundClose, NULL);
	soundsItem->setPosition(Point(origin.x + visiableSize.width / 2 , origin.y + visiableSize.height / 2 - 50));

	auto menu = Menu::create(startItem, soundsItem, NULL);
	menu->setPosition(origin.x, origin.y);
	this->addChild(menu);

	//对手机返回键的监听
	auto listener = EventListenerKeyboard::create();
	//和回调函数绑定
	listener->onKeyReleased = CC_CALLBACK_2(WelcomeScene::onKeyReleased, this);
	//添加到事件分发器中
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void WelcomeScene::menuStartCallback(Object *sender){
	auto scene = LevelSelectScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void WelcomeScene::menuMusicCallback(Object *sender)
{
	if (_isMusicOpen)
	{
		SimpleAudioEngine::getInstance()->setEffectsVolume(0);
		_isMusicOpen = false;
	}
	else
	{
		SimpleAudioEngine::getInstance()->setEffectsVolume(1);
		_isMusicOpen = true;
		SimpleAudioEngine::getInstance()->playEffect("sounds/whenDian.wav");
	}
}

void WelcomeScene::menuScoreCallback(Object *sender)
{

}

//返回键关闭
void WelcomeScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo method;
	std::string className = "org/cocos2dx/lib/MainActivity";
	if (JniHelper::getStaticMethodInfo(method, className.c_str(), "rtnObject", "()Ljava/lang/Object;"))
	{
		jobject jobj;
		jobj = method.env->CallStaticObjectMethod(method.classID, method.methodID);

		if (JniHelper::getMethodInfo(method, className.c_str(), "Login", "()V"))
		{
			method.env->CallVoidMethod(jobj, method.methodID);
		}
	}
#else
	Director::getInstance()->end();
	//exit(0);
#endif
}