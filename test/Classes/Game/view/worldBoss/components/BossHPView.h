#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class BossHPView : public CCLayer
{
public:
	BossHPView();
	virtual ~BossHPView();

	virtual bool init();

	void loadItems();

	void updateHP(float dt , int curhp = -1, int maxhp = -1 , float percent = 1);

public:
	enum ITEM_TAG
	{
		TAG_BloodBar = 121,
		TAG_BloodText = 122,
	};

	CCSize _winSize;

protected:
private:
};