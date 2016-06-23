#ifndef _SHOPMEDIATOR_H_
#define _SHOPMEDIATOR_H_

#include "mvc/Mediator.h"

class GameDispatcher;
class ShopView;

class ShopMediator:public Mediator
{
public:
	ShopMediator();
	~ShopMediator();


	void shopPopHandler(CCNode* p, void* e);
	void openShopView();
	void shopBuy(CCNode* p, void* e);
	void onSellGridAlert(int32 sit);
	void onBuyGridAlert(int32 id);
	void okSellItem(CCObject* pSender);
	void okSellItemCancel(CCObject* pSender);
	void okSellItemQuality4(CCObject* pSender);
public:
	int32 _shopId;
	ShopView* _shopView;
	GameDispatcher* _dispatcher;
	int32 e_param_sit;
	int32 e_param_sellvalue;
};

#endif