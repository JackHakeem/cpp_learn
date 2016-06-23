#ifndef _TraderGoodsVo_H_
#define _TraderGoodsVo_H_

#include "BaseType.h"

class TraderGoodsVo
{
public:
	TraderGoodsVo()
	{
		goodsName = "";
		goodsId = 0;
		icon = 0;
		price = 0;
	}
	~TraderGoodsVo()
	{
	}

public:
	int goodsId;
	string goodsName;
	int icon;
	int price;
};
#endif