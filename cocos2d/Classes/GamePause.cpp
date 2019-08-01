#include "Gamepause.h" 
#include "LevelSelectScene.h"

Scene* GamePause::scene(RenderTexture* sqr)
{
	Scene *scene = Scene::create();
	GamePause *layer = GamePause::create();
	scene->addChild(layer, 1);
	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite 
	//����Sprite��ӵ�GamePause��������  
	//�õ����ڵĴ�С  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(visibleSize.width / 2, visibleSize.height / 2); //����λ��,������������λ�á�  
	back_spr->setFlipY(true);            //��ת����ΪUI�����OpenGL���겻ͬ  
	back_spr->setColor(Color3B::GRAY); //ͼƬ��ɫ���ɫ  
	scene->addChild(back_spr);
	return scene;
}

bool GamePause::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//�õ����ڵĴ�С  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//ԭ������  
	Point origin = Director::getInstance()->getVisibleOrigin();

	//������Ϸ��ť  
	MenuItemImage *pContinueItem = MenuItemImage::create("image/CloseNormal.png", "image/CloseSelected.png",
		CC_CALLBACK_1(GamePause::menuContinueCallback, this));
	pContinueItem->setPosition(visibleSize.width / 2 + 25, visibleSize.height / 2 + 30);

	MenuItemImage *pBackItem = MenuItemImage::create("image/back.png", "image/back.png",
		CC_CALLBACK_1(GamePause::menuBackCallback, this));
	pBackItem->setPosition(visibleSize.width / 2 - 25, visibleSize.height / 2 + 30);

	Menu* pMenu = Menu::create(pContinueItem, pBackItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 2);
	//����������
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
	//���ͷŶ�ջ�ĳ���
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