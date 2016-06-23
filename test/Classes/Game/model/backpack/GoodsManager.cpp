#include "GoodsManager.h"



GoodsManager* g_pGoodsManager = 0;

GoodsManager::GoodsManager()
{

}

GoodsManager::~GoodsManager()
{
	std::map< int, GoodsBasic* >::iterator it;
	for ( it = _goodsBasic.begin(); it != _goodsBasic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_goodsBasic.clear();
}

int32 GoodsManager::addGood(GoodsBasic* p)
{
	if (!p) 
	{
		//Pointer for 0
		return 1;
	}
	//cocos2d::CCLog("%d   %s \n", p->goodId, p->intro.c_str());
	//printf("%d   %s \n", p->goodId, p->goodName);

	_goodsBasic.insert(std::map<uint32, GoodsBasic*>::value_type(p->goodId,p));
	return 0;
}

/**
	* 根据等级、类型获取物品(PS：装备出处查看专用)
	* @param level
	* @param type
	* @return 
	* 
	*/		
void GoodsManager::getEquips(int level, int type, std::vector<GoodsBasic*>& dstEQ)//kevin0830
{
	//dstEQ.clear();
	GoodsBasic* goods = 0;
	for (std::map<int, GoodsBasic*>::iterator it = _goodsBasic.begin(); it != _goodsBasic.end(); it++)
	{
		goods = it->second;
		if (!goods)
			continue;

		if(goods->type == 2 && goods->level == level && goods->equip_type == type && goods->drop_from.size() > 0 && goods->drop_from != "0")
		{
			dstEQ.push_back(goods);
		}
	}
}