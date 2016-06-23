#ifndef _SHOPMANAGER_H 
#define _SHOPMANAGER_H 

#include "BaseType.h"
#include "vo/shopVo.h"
#include "utils/Singleton.h"
//using namespace util;


class ShopManager: public Singleton<ShopManager>
{
public:
	ShopManager()
	{
	}
	~ShopManager();

public:
	ShopVo* allocVo() { return new ShopVo(); };

	void createShops(ShopVo* pShopVo);
	ShopVo* getShopsByNPCId(int npcid);
	int getIconByType(int type);
	int getIconByNPCID( int iNPCID );

private:
	//private var _shopGoods:Dictionary;
	//private static var _instance:ShopManage;
	//public static const jobList:Array = ["任何职业", "昆仑", "逍遥", "唐门"];
	//public static const propList:Array = ["末知", "气血", "内力", "攻击", "防御", "命中", "躲避", "暴击", "坚韧"];

	std::map<int, ShopVo*> _shops;		//According to the NPC storage
};

typedef std::map<int, ShopVo*>::iterator SHOPVOITER;

#endif