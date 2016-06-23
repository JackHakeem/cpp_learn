#ifndef _APPOINT_MEDIATOR_H_
#define _APPOINT_MEDIATOR_H_
#include "mvc/Mediator.h"
#include "socket/command/s1e/SCMD1E1.h"
#include "socket/command/s1e/SCMD1E3.h"
#include "socket/command/s1e/SCMD1E6.h"
#include "socket/command/s1d/SCMD1DD.h"
#include "socket/command/s1d/SCMD1DB.h"
#include "components/GoodsView.h"
#include "components/AppointView.h"

class AppointMediator : public Mediator
{
public:
	AppointMediator();
	enum 
	{
		INIT_FINISHI = 0,
		UPDATE_TRADER_INFO,
		GOODS_DOUBLE_CLICK,
		APPOINT_TRADER,
		RECEIVE_ALL,
		SELL_ALL,
		ON_TRADER_CLICK,
	};

	void getAppointInfo(SCMD1E1 *pData);
	void getAppointResult(SCMD1E3 *pData);
	void getAppointGoods(SCMD1E6 *pData);
	void getAppointBlessInfo(SCMD1DD *pData);
	void getExchangeResult(SCMD1DB *pData);
	void appointBlessExchange(CCNode *pNode, void *pData);
	void exchangeHandler(CCNode *pNode, void *pData);
	void initFinish();

	void popHandler(CCNode *pNode, void *pData);
	void openAppointBlessView(CCNode *pNode, void *pData);
	void openAppointView();
	void updateGoldAppoint(CCNode *pNode, void *pData);
	void startViewListener();
	void onGoodsDoubleClick(int goodsId);
	void appointTrader(CCNode *pNode, void *pData);
	void receiveAll(CCNode *pNode, void *pData);
	void sellAll(CCNode *pNode, void *pData);
	void onTraderClick(CCNode *pNode, void *pData);
	void blessValueChange(CCNode *pNode, void *pData);
	void blessTotalChange(CCNode *pNode, void *pData);

	virtual void handleNotification( int M2Vcmd, char* data );

	AppointView *_pAppointView;
	std::list<GoodsView *> _goods;
};

#endif