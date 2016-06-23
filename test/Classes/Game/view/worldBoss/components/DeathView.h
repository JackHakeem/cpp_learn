#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class DeathView : public CCLayer
{
public:
	DeathView();
	virtual ~DeathView();

	virtual bool init();

	void loadItems();

	void requestReborn(CCObject * pSender);
	void requestRelive(CCObject * pSender);
	void updateCD(int nMoveCD);

	void runCD();
	void stopCD();
	void step(ccTime dt);

	void onRequestConfirm(CCObject * pSender);
	void onCancel(CCObject * pSender);

	enum
	{
		TAG_CD = 121,
	};

	CCPoint _menuPos;
	CCSize _winSize;
	int _nCount;
	bool _isInCD;

protected:
private:
};