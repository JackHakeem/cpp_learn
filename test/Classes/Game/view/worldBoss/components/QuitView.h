#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class QuitView : public CCLayer
{
public:
	QuitView();
	virtual ~QuitView();

	virtual bool init();

	void loadItems();

	void onClickQuit(CCObject * pSender);

	void updateCD(int nActivityCD);

	void runActivityCD( int lefttime);

	void step(ccTime dt);

	void updateCDText(int timeSecond);

	void updateBossHP(float percent);

	enum
	{
		TAG_CD = 121,
		TAG_CD_Second,
	};

	CCPoint _menuPos;
	int _nLeftTime;
	int _nTimeCount;
	CCSize _winSize;

protected:
private:
};