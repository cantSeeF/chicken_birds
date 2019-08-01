#pragma once

#include "cocos2d.h"
#include "Chicken.h"
#include "StatusLayer.h"
#include "NormalBird.h"
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "egg.h"
#include "SomeDate.h"

using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

class GameLayer : public Layer{
public:
	GameLayer();
	~GameLayer();
	bool virtual init();
	CREATE_FUNC(GameLayer);
	CC_SYNTHESIZE(StatusDelegate*,delegator, Delegator);

	virtual bool onTouchBegan(Touch* touch, Event* event);
	//��ײ
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual void onContactSeparate(PhysicsContact& contact);
	//������Ӧ
	void onAcceleration(Acceleration* acc, Event* event);

	void update(float delta);
	//������Ļ
	void getbackToScreen();
	//����ji�ƶ�
	void chickenMoveControl();
	//��ĸ��
	void addBird();
	//�������
	void addWorld();
	//�Ե����� �Զ��������:schedule(SEL_SCHEDULE selector, float interval��ÿ�ε���ʱ������, unsigned int repeat��������, float delay����һ�ε��ü����)
	void eggSurprise();
	//�ָ�ĸ���ٶ�
	void getBackBirdSpeed(float dt);
	//�ָ�ĸ��
	void addABird(float dt);
	//����
	void chickenRebirth(float dt);
	//����޵�
	void chickenNotInvicible(float dt);
	//�����ı�
	void weatherChange();
	//����Ч��
	void addParticle();
	void deathBond(Point point);
	void removeDBond();
	void gameOver();
private:
	GameStatus _gameStatus;
	int _score;
	int _life;
	Chicken *_chicken;
	float _xLast;
	float _yLast;
	//��ĸ��
	Vector<NormalBird*> _birds;
	Vector<Egg*> _eggs;
	bool _speedStatus;
	bool _isInvicible;
	Point _origin;
	Size _visiableSize;
};
