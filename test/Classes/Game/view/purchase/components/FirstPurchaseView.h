#ifndef _FIRST_PURCHASE_VIEW_H_
#define _FIRST_PURCHASE_VIEW_H_

#include "cocos2d.h"
#include "PopContainer.h"
#include "BaseType.h"

class FirstPurchaseView : public PopContainer
{
public:
	FirstPurchaseView();
	~FirstPurchaseView(){}

	virtual bool init();

	void onBuyButtonClick(CCObject* pSender);
};
#endif