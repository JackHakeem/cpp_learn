#ifndef _TraderView_H_
#define _TraderView_H_

#include "BaseType.h"
#include "PopContainer.h"
#include "model/trader/vo/CityPriceVo.h"
#include "model/trader/vo/BankGridVo.h"
#include "model/trader/vo/TraderEventVo.h"
#include "model/player/RoleManage.h"
#include "TraderGoodsItem.h"
#include "CCUIBackground.h"

class TraderView : public PopContainer
{
public:
	TraderView();
	~TraderView();

public:
	enum
	{
		OPEN_CITY_PANEL,
		BUY_ITEM,
		REFRESH_GOODS,
		UNLOCK_BANKS,
		GO_TRADE,
	};
	bool init();
	LAYER_NODE_FUNC(TraderView);

	virtual void clickCloseHandler(CCObject* pSender);

	void buyNumChange(int num);
	void cityChange( CityPriceVo* vo );
	void historyChange( std::list<int> _historyList );
	void showTraderGoods( std::list<int> _itemList );
	void showBankGoods( std::list<BankGridVo*> _bankList );
	void eventChange( std::list<TraderEventVo*> _eventList );
	void clearGoods();
	void tradeHandler(CCObject* obj);
	void refreshHandler(CCObject* obj);
	CityPriceVo* getHighestPrice(std::list<CityPriceVo*>& cityList, int mapId);

	void registerWithTouchDispatcher( void );
	bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
	static float GetGoodQuality( int goodsId );
	static int getBasePop( int goodsId );
	ccColor3B getTradeColor( int goodsId );
	CCUIBackground* _bgSkillTips;
public:
	CCLayer* pInnerLayer;
	CCUIBackground* _infoContainer;

	//bankDic;
	std::list<TraderGoodsItem*> goodArr;
	//historyDic;
	
	CCMenu* _btnRefresh;
	CCMenu* _starTrade;
	int _vipLv;
	int _silever;
	int _refreshCost;
	CCMenu* _btnGo;
	bool _hasGoods;
	bool _hasDest;
	//_conditionTips:TipHelps;
	int _mapId;
	int _restNum;
	bool _isFull;
	int _lockGrid;
	RoleManage* _roleManage;

	CCLabelTTF* _txtRestTrader;
	CCLabelTTF* _txtRestTraderCnt;

	CCSprite* _needGoldPic;
	CCUIBackground* m_selectedSpriteImage;

	int _curGood;
	bool _clickRefresh;
};

#endif