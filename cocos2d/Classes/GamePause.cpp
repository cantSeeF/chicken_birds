#include "Gamepause.h" 
#include "LevelSelectScene.h"

Scene* GamePause::scene(RenderTexture* sqr)
{
	Scene *scene = Scene::create();
	GamePause *layer = GamePause::create();
	scene->addChild(layer, 1);
	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite 
	//并将Sprite添加到GamePause场景层中  
	//得到窗口的大小  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(visibleSize.width / 2, visibleSize.height / 2); //放置位置,这个相对于中心位置。  
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同  
	back_spr->setColor(Color3B::GRAY); //图片颜色变灰色  
	scene->addChild(back_spr);
	return scene;
}

bool GamePause::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//得到窗口的大小  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//原点坐标  
	Point origin = Director::getInstance()->getVisibleOrigin();

	//继续游戏按钮  
	MenuItemImage *pContinueItem = MenuItemImage::create("image/CloseNormal.png", "image/CloseSelected.png",
		CC_CALLBACK_1(GamePause::menuContinueCallback, this));
	pContinueItem->setPosition(visibleSize.width / 2 + 25, visibleSize.height / 2 + 30);

	MenuItemImage *pBackItem = MenuItemImage::create("image/back.png", "image/back.png",
		CC_CALLBACK_1(GamePause::menuBackCallback, this));
	pBackItem->setPosition(visibleSize.width / 2 - 25, visibleSize.height / 2 + 30);

	Menu* pMenu = Menu::create(pContinueItem, pBackItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 2);
	//设置灵敏度
	ControlSlider *slider = ControlSlider::create("image/rectangle2.png","image/rectangle.png",  "image/feather.png");

	slider->setMinimumAllowedValue(0.0f);
	slider->setMaximumAllowedValue(5.0f);
	slider->setValue((UserDefault::getInstance()->getFloatForKey("response", 60) - 40) / 40);
	slider->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 30);
	slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GamePause::valueChanged), Control::EventType::VALUE_CHANGED);

	this->addChild(slider);
	
	auto *sensibility = Sprite::create("image/sensibility.png");
	sensibility->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 60);
	this->addChild(sensibility);

	return true;
}

void GamePause::menuContinueCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}

void GamePause::menuBackCallback(Ref* pSender)
{
	//先释放堆栈的场景
	Director::getInstance()->popScene();
	auto scene = LevelSelectScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void GamePause::valueChanged(Ref *sender, Control::EventType controlEvent)
{
	ControlSlider *pSlider = (ControlSlider*)sender;
	//log("value=%f,maxValue=%f", pSlider->getValue(),pSlider->getMaximumValue());
	UserDefault::getInstance()->setFloatForKey("response", pSlider->getValue() * 40 + 40);
	//SimpleAudioEngine::getInstance()->playEffect("sounds/whenWin.wav");
}