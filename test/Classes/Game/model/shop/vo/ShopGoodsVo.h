#ifndef _SHOPGOODSVO_H_
#define _SHOPGOODSVO_H_

#include "BaseType.h"	

class ShopGoodsVo
{
public:
	int32 shopid;		
	int32 goodsid;
	std::string name;
	int32 price;
	int32 sitGrid;
};

#endif