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
	//public static const jobList:Array = ["�κ�ְҵ", "����", "��ң", "����"];
	//public static const propList:Array = ["ĩ֪", "��Ѫ", "����", "����", "����", "����", "���", "����", "����"];

	std::map<int, ShopVo*> _shops;		//According to the NPC storage
};

typedef std::map<int, ShopVo*>::iterator SHOPVOITER;

#endif