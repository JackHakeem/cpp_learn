#ifndef _CityTraderInfoVo_H_
#define _CityTraderInfoVo_H_

#include "BaseType.h"
#include "TowerRankItemVo.h"

class CityTraderInfoVo
{
public:
	CityTraderInfoVo()
	{
		isVip = false;
		restTimes = 0;
	}
	~CityTraderInfoVo()
	{
	}

public:
	bool isVip;
	int restTimes;
};
#endif