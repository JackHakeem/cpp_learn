#include "TraderProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

TraderProxy::TraderProxy()
{
	numReady = false;
	bankReady = false;
	_buyNum = 0;
	selectedVo = 0;

	_refreshCnt = 0;
	_beatedCnt = 0;
	_buyTokenCnt = 0;
	_traderState = Trader_State_none;
	_robedSilver = 0;
	_currentMapId = 0;

	_restTraderCnt = -1;
	_robedPop = 0;
}

TraderProxy::~TraderProxy()
{
	std::list<TraderEventVo*>::iterator it = _eventList.begin();
	for ( ; it != _eventList.end(); it++ )
	{
		TraderEventVo* vo = *it;
		CC_SAFE_DELETE( vo );
	}
	_eventList.clear();
}

int TraderProxy::getBasePop()
{
	if (_itemList.size()==0)
	{
		return 0;
	}
	int good = *_itemList.begin();
	switch(good)
	{
	case 1:
		return 100/2;
		break;
	case 2:
		return 200/2;
		break;
	case 3:
		return 300/2;
		break;
	case 4:
		return 600/2;
		break;
	case 5:
		return 1000/2;
		break;
	}
	return 0;
}

void TraderProxy::setbuyNum(int num){
	_buyNum = num;
}
int TraderProxy::getbuyNum(){
	return _buyNum;
}

float TraderProxy::GetGoodQuality() const
{
	if (_itemList.size()==0)
	{
		return 0.0f;
	}
	int good = *_itemList.begin();

	switch (good)
	{
	case 1:
		return 1.0f;
		break;
	case 2:
		return 1.5f;
		break;
	case 3:
		return 2.0f;
		break;
	case 4:
		return 4.0f;
		break;
	case 5:
		return 8.0f;
		break;
	}

	return 0.0f;
}

ccColor3B TraderProxy::getTradeColor()
{
	if (_itemList.size()==0)
	{
		return ccGREEN;
	}
	int good = *_itemList.begin();

	switch (good)
	{
	case 1:
		return ccGREEN;
		break;
	case 2:
		return ccc3(0, 168, 255);
		break;
	case 3:
		return ccc3(0x99, 0x32, 0xCD);//9932CD
		break;
	case 4:
		return ccc3(255, 124, 0);
		break;
	case 5:
		return ccRED;
		break;
	}

	return ccGREEN;
}

ccColor3B TraderProxy::getTradeColor(int col)
{
	switch (col)
	{
	case 1:
		return ccGREEN;
		break;
	case 2:
		return ccc3(0, 168, 255);
		break;
	case 3:
		return ccc3(0x99, 0x32, 0xCD);//9932CD
		break;
	case 4:
		return ccc3(255, 124, 0);
		break;
	case 5:
		return ccRED;
		break;
	}

	return ccGREEN;
}