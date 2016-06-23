#include "ShopManage.h"

ShopManage* g_pShopManage = 0;

ShopManage::ShopManage()
{

}

ShopManage::~ShopManage()
{
}

int32 ShopManage::createGoods(int32 shopid, ShopGoodsVo& shopGood)
{
	std::map<int, std::vector<ShopGoodsVo> >::iterator it = _shopGoods.find(shopid);
	if (it == _shopGoods.end())
	{
		std::vector<ShopGoodsVo> tmpv;
		tmpv.push_back(shopGood);
		_shopGoods.insert(std::make_pair(shopid, tmpv));
	}
	else
	{
		std::vector<ShopGoodsVo>& tmpv = it->second;
		tmpv.push_back(shopGood);
	}
	return 0;
}

int32 ShopManage::createShops(int32 npcid, ShopVo& shop)
{
	std::map<int, std::vector<ShopVo> >::iterator it = _shops.find(npcid);
	if (it == _shops.end())
	{
		std::vector<ShopVo> tmpv;
		tmpv.push_back(shop);
		_shops.insert(std::make_pair(npcid, tmpv));
	}
	else
	{
		std::vector<ShopVo>& tmpv = it->second;
		tmpv.push_back(shop);
	}
	return 0;
	
}
/**
	*  According to different map for different goods
	* @param id
	* @return 
	* 
	*/
std::vector<ShopGoodsVo>* ShopManage::getGoodsByShopId(int id)
{
	std::map<int, std::vector<ShopGoodsVo> >::iterator it = _shopGoods.find(id);
	if (it != _shopGoods.end())
	{
		return &(it->second);
	}
	return 0;
}

/**
	*   According to npcid to obtain its body, which have function such as the black market entry recruitment
	* @param id
	* @return 
	* 
	*/		
std::vector<ShopVo>* ShopManage::getShopsByNPCId(int npcid)
{
	std::map<int, std::vector<ShopVo> >::iterator it = _shops.find(npcid);
	if (it != _shops.end())
	{
		return &(it->second);
	}
	return 0;
}