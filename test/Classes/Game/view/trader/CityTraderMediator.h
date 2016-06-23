#ifndef _CityTraderMediator_H_
#define _CityTraderMediator_H_

#include "BaseType.h"
#include "mvc/Mediator.h"
#include "components/TraderView.h"
#include "socket/command/s2b/SCMD2B1.h"
#include "socket/command/s2b/SCMD2B2.h"
#include "socket/command/s2b/SCMD2B3.h"
#include "socket/command/s2b/SCMD2B4.h"
#include "socket/command/s2b/SCMD2B6.h"
#include "socket/command/s2b/SCMD2B7.h"
#include "socket/command/s2b/SCMD2B9.h"
#include "socket/command/s2b/SCMD2BB.h"
#include "socket/command/s2b/SCMD2BF.h"
#include "socket/command/s2c/SCMD2C3.h"
#include "socket/command/s2c/SCMD2C4.h"
#include "socket/command/s2c/SCMD2C5.h"
#include "socket/command/c13/CCMD134.h"
#include "model/trader/TraderProxy.h"
#include "components/RobPanel.h"
#include "model/scene/vo/FindVo.h"
#include "components/MyRobPanel.h"
#include "socket/command/s28/SCMD28F.h"

class CityTraderMediator:public Mediator
{
public:
	CityTraderMediator();
	~CityTraderMediator();
	enum
	{
		UPDATE_HISTORY_LIST,
		UPDATE_GOODS_LIST,
		UPDATE_BANK_LIST,
		UPDATE_EVENT_LIST,
		UPDATE_CITY_PRICE_LIST,
		END_BUSINESS_PROCESS,
		START_RUNNING_BUSINESS,
	};
public:
	void handleNotification( int M2Vcmd, char* data );
	void initTrader(CCNode* n, void* data);
	void initRob(CCNode* n, void* data);
	void openHandler();
	void open();
	void openTraderView();
	void openRob();
	void closeHandler(CCNode* n, void* data);
	void initViewListeners();
	void updateHistory();
	void updateGoods();
	void updateBank();
	void updateEvent();
	void updateCity();
	void eventListHandler( SCMD2B1* param );
	void goodsListHandler(SCMD2B2* param );
	void bankListHandler(SCMD2B3* param);
	void historyListHandler(SCMD2B4* param);
	void cityPriceHandler(SCMD2B6* param);
	void reachEventHandler(SCMD2B7* param);
	void startBusiness(SCMD2B9* cmd);
	void endBusiness(SCMD2BB* cmd);
	void robInfoPop(SCMD2BF* cmd);
	void robReply(SCMD2C3* cmd);
	void robResultHandler(SCMD2C4* cmd);
	void robNoteHandler(SCMD2C5* cmd);
	void watchThatDamnReport(CCMD134* param);
	void refreshHandler(CCNode* n, void* data);
	void citySelectHandler(CCNode* n, void* data);
	void buyHandler(CCNode* n, void* data);
	void goTradeHandler(CCNode* n, void* data);
	void unlockHandler(CCNode* n, void* data);
	void reqEndBusiness();
	void robHim(CCNode* n, void* data);
	void openCityPanel(CCNode* n, void* data);
	void startRunningBusiness( FindVo* vo );
	void openMyRob();
	void updateRobInfoGet( SCMD28F* param );
public:
	TraderView* _traderView;
	int _traderViewType;
	//_cityPanel:CitySelectPanel;
	RobPanel* _robPanel;
	MyRobPanel* _myRobPanel;

	int _type;
	string _name;
	int _id;
	int _lv;
	CCSprite* _alertBtn;
	int _num;            //Œª÷√À≥–Ú
	int _sequence;      //µΩ¥ÔÀ≥–Ú
	bool _initListener;
	TraderProxy* _traderProxy;
	std::list<SCMD2C5> _msgDic;
};

extern CityTraderMediator* g_pCityTraderMediator;
#endif