#ifndef _APPOINT_MANAGER_H_
#define _APPOINT_MANAGER_H_
#include "BaseType.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "utils/Singleton.h"
#include "vo/AppointBlessVo.h"
#include "vo/AppointVo.h"
#include "view/appoint/components/GoodsView.h"

class AppointManager : public Singleton<AppointManager>, public CCIEventDispatcher
{
public:
	AppointManager() 
	{
		_blessValue = 0;
		_blessTotal = 0;
	}

	enum
	{
		BLESS_VALUE_CHANGE = 0,
		BLESS_TOTAL_CHANGE
	};
	
	void setAppointTraders(AppointVo *pTrader);
	void setBlessVo(AppointBlessVo *pAppointBlessVo);
	AppointVo *getTraderVoByLev(int type, int lev);
	AppointVo *getTraderVoByBit(int type, int bitNum);
	int getHighestLev(int bitNum);
	void setBlessValue(int value);
	int getBlessValue();
	void setBlessTotal(int total);
	int getBlessTotal();
	std::list<AppointBlessVo *> &getAppointBlessArr();

	std::list<GoodsView *> _goodsArr;
	std::list<AppointBlessVo *> _appointBlessArr;
private:

	std::list<AppointVo *> _appointDict;		//key:id, value:TraderVo
	//public var goodsArr:Array = [];				//key:id, value:GoodsView
	int _blessValue;		//ÌÔ±¦×£¸£Öµ
	int _blessTotal;		//ÌÔ±¦×£¸£ÖµÉÏÏÞ
};
#endif