#ifndef _TraderProxy_H_
#define _TraderProxy_H_

#include "mvc/Proxy.h"
#include "vo/TraderEventVo.h"
#include "vo/BankGridVo.h"
#include "vo/CityPriceVo.h"

class TraderProxy: public Proxy
{
public:
	TraderProxy();
	~TraderProxy();
	void setbuyNum(int num);
	int getbuyNum();

	float GetGoodQuality() const;
	int getBasePop();
	ccColor3B getTradeColor();
	static ccColor3B getTradeColor(int col);
	enum TraderState
	{
		Trader_State_none,
		Trader_State_City1,
		Trader_State_City2,
	};

public:
	std::list<TraderEventVo*> _eventList;               //达成时间存放列表
	std::list<BankGridVo*> _bankList;                //仓库物品列表
	std::list<int> _historyList;             //历史记录列表
	std::list<CityPriceVo*> _cityPriceList;		 //各个主城的商品价格
	int _buyNum;
	std::list<int> _itemList;
	CityPriceVo* selectedVo;			//玩家选择的目的城市vo
	bool numReady;
	bool bankReady;

	int _refreshCnt;
	int _beatedCnt;

	int _buyTokenCnt;

	int _robedSilver;
	TraderState _traderState;
	int _currentMapId;

	int _restTraderCnt;
	int _robedPop;
};

#endif