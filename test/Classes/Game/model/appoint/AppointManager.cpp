#include "AppointManager.h"

void AppointManager::setAppointTraders( AppointVo *pTrader )
{
	_appointDict.push_back(pTrader);
}

void AppointManager::setBlessVo( AppointBlessVo *pAppointBlessVo )
{
	_appointBlessArr.push_back(pAppointBlessVo);
}

AppointVo * AppointManager::getTraderVoByLev( int type, int lev )
{
	std::list<AppointVo *>::iterator it;
	for(it = _appointDict.begin(); it != _appointDict.end(); ++it)
	{
		AppointVo *pAppointVo = (AppointVo *) *it;
		if(pAppointVo && 
			pAppointVo->type == type &&
			pAppointVo->level == lev)
		{
			return pAppointVo;
		}
	}
	return NULL;
}

AppointVo * AppointManager::getTraderVoByBit( int type, int bitNum )
{
	std::list<AppointVo *>::iterator it;
	for(it = _appointDict.begin(); it != _appointDict.end(); ++it)
	{
		AppointVo *pAppointVo = (AppointVo *) *it;
		if(pAppointVo && 
			pAppointVo->type == type &&
			pAppointVo->bitNum == bitNum)
		{
			return pAppointVo;
		}
	}
	return NULL;
}

int AppointManager::getHighestLev( int bitNum )
{
	if(bitNum & 1)
	{
		return 3;
	}
	else if(bitNum & 2)
	{
		return 2;
	}
	else if(bitNum & 4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void AppointManager::setBlessValue( int value )
{
	_blessValue = value;
	dispatchEvent(BLESS_VALUE_CHANGE, NULL);
}

int AppointManager::getBlessValue()
{
	return _blessValue;
}

void AppointManager::setBlessTotal( int total )
{
	_blessTotal = total;
	dispatchEvent(BLESS_TOTAL_CHANGE, NULL);
}

int AppointManager::getBlessTotal()
{
	return _blessTotal;
}

std::list<AppointBlessVo *> &AppointManager::getAppointBlessArr()
{
	return _appointBlessArr;
}



