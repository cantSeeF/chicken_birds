#include "BackgroundLayer.h"
BackgroundLayer::BackgroundLayer(){};
BackgroundLayer::~BackgroundLayer(){};

bool BackgroundLayer::init(){
	if (!Layer::init()){
		return false;
	}
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Sprite *background;
	background = Sprite::create("image/00.png");
	background->setPosition(origin.x + visiableSize.width / 2, origin.y + visiableSize.height / 2);
	this->addChild(background);
	return true;
}