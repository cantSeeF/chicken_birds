#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init(){
	if (Scene::initWithPhysics()){
		//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		this->getPhysicsWorld()->setGravity(Vect(0, -500));
		auto backgroundLayer = BackgroundLayer::create();
		if (backgroundLayer) {
			this->addChild(backgroundLayer);
		}

		auto statusLayer = StatusLayer::create();
		// Add the main game layer
		switch (UserDefault::getInstance()->getIntegerForKey("levelSelect",1))
		//switch (1)
		{
		case 1:
		{
			auto *gameLayer = GameLayer1::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		case 2:
		{
			auto *gameLayer = GameLayer2::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		case 3:
		{
			auto *gameLayer = GameLayer3::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		case 4:
		{
			auto *gameLayer = GameLayer4::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		case 5:
		{
			auto *gameLayer = GameLayer5::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		case 6:
		{
			auto *gameLayer = GameLayer6::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		case 7:
		{
			auto *gameLayer = GameLayer7::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		case 8:
		{
			auto *gameLayer = GameLayer8::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		case 9:
		{
			auto *gameLayer = GameLayer9::create();
			if (gameLayer) {
				gameLayer->setDelegator(statusLayer);
				gameLayer->showScore();
				this->addChild(gameLayer);
			}
		}
			break;
		}

		if (statusLayer){
			this->addChild(statusLayer);
		}
		return true;
	}
	else {
		return false;
	}
}

void GameScene::restart() {
	this->removeAllChildrenWithCleanup(true);
	this->init();
}
