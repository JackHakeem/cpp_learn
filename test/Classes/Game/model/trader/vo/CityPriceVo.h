#ifndef _CityPriceVo_H_
#define _CityPriceVo_H_

#include "BaseType.h"

class CityPriceVo
{
public:
	CityPriceVo()
	{
		mapId = 0;
		cityName = "";
		cityPrice = 0;
		npcId = 0;
	}
	~CityPriceVo()
	{
	}

public:
	int mapId;
	string cityName;
	int cityPrice;
	int npcId;
};
#endif