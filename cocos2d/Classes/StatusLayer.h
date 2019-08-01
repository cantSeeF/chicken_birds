#pragma once

#include"cocos2d.h"
#include"GamePause.h"

USING_NS_CC;
using namespace std;

class StatusDelegate {
public:
	virtual void onGameStart(void) = 0;
	virtual void onGamePlaying(int score) = 0;
	virtual void showLifes(int life) = 0;
	virtual void onGameEnd(int curSocre) = 0;
	virtual void onGameWin() = 0;
};

class StatusLayer :public Layer,public StatusDelegate
{
public:
	StatusLayer(void){}
	~StatusLayer(void){}
	virtual bool init();

	CREATE_FUNC(StatusLayer);

	void onGameStart(){}
	void onGamePlaying(int score);
	void showLifes(int life);
	void onGameEnd(int curScore);
	void onGameWin();
	//ÔÝÍ£
	void menuPauseCallback(Ref* pSender);
	//ÊÖ»ú·µ»Ø¼ü
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
	void fadeInGameOver();
	void jumpToScorePanel();
	void fadeInRestartBtn();
	void menuRestartCallback(Ref* pSender);
	void menuNextLevelCallback(Ref* pSender);
private:
	Vector<Sprite*> _eggLife;
	int _currentScore;
	int _tmpScore;
	bool _isNewRecord;
	Point _origin;
	Size _visibleSize;
};