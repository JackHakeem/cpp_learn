#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class BoostView : public CCLayer
{
public:
	BoostView();
	virtual ~BoostView();

	virtual bool init();

	void loadItems();

	void requestGoldBoost(CCObject * pSender);
	void requestPracBoost(CCObject * pSender);

	void onRequestConfirm(CCObject * pSender);
	void onCancel(CCObject * pSender);

	void resetBoostResultText(int percent);
	void lockBtn(ccTime dt);
public:
	enum ITEM_TAG
	{
		TAG_Boost_text = 121,
	};

	CCSize _winSize;

protected:
private:
};