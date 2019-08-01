#pragma once

#include "cocos2d.h"
#include "Chicken.h"
#include "StatusLayer.h"
#include "NormalBird.h"
#include "RedBird.h"
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "egg.h"
#include "SomeDate.h"

using namespace std;
using namespace CocosDenshion;
USING_NS_CC;

class GameLayer9 : public Layer{
public:
	GameLayer9();
	~GameLayer9();
	bool virtual init();
	void onEnter();
	void virtual onExitTransitionDidStart();
	CREATE_FUNC(GameLayer9);
	CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);

	virtual bool onTouchBegan(Touch* touch, Event* event);
	//��ײ
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual void onContactSeparate(PhysicsContact& contact);
	//������Ӧ
	void onAcceleration(Acceleration* acc, Event* event);

	void update(float delta);
	//������Ļ
	void getbackToScreen();
	//�������ƶ�
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
	//����Ч��
	void addParticle();
	void deathBond(Point point);
	void removeDBond();
	void gameOver();
	void gameWin();
	void showScore();
private:
	GameStatus _gameStatus;
	int _life;
	int _response;
	int _needScore;
	Chicken *_chicken;
	float _xLast;
	float _yLast;
	//����
	Vector<Sprite*> _birds;
	Vector<Egg*> _eggs;
	bool _speedStatus;
	bool _isInvicible;
	Point _origin;
	Size _visiableSize;
};
