#ifndef _SHOPMANAGE_H_
#define _SHOPMANAGE_H_

#include "vo/shopVo.h"
#include "vo/ShopGoodsVo.h"

class ShopManage
{
public:
	ShopManage();
	~ShopManage();

	int32 createGoods(int32 shopid, ShopGoodsVo& shopGood);
	int32 createShops(int32 npcid, ShopVo& shop);
	std::vector<ShopGoodsVo>* getGoodsByShopId(int id);
	std::vector<ShopVo>* getShopsByNPCId(int npcid);

private:
	std::map<int, std::vector<ShopVo> > _shops;
	std::map<int, std::vector<ShopGoodsVo> > _shopGoods;
};

extern ShopManage* g_pShopManage;

#endif
