#include "BagProxy.h"
#include "view/backpack/BagMediator.h"
#include "control/AppFacade.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/GoodsManager.h"
#include "model/com/GoodsToolTips.h"
#include "model/com/GoodsDynamicManager.h"



BagProxy::BagProxy()
{
	_goodsNumber = 0;
	_noEmpty = 0;
}

BagProxy::~BagProxy()
{
	std::map<int32, GoodsInfo*>::iterator it;
	for ( it = _goodsList.begin(); it != _goodsList.end(); it++ )
	{
		if ( it->second )
		{
			//CC_SAFE_DELETE( it->second->explain );
            CC_SAFE_DELETE( it->second );
		}
		
	}
	_goodsList.clear(); // LH0714
}

void BagProxy::createList(char* data)
{
	if (!data)
	{
		CCLog("error void BagProxy::createList(char* data)");
	}
	std::list<SCMD161_163_165_167Node>* tmpdata = (std::list<SCMD161_163_165_167Node>*)data;
	_goodsNumber = tmpdata->size();
	//DATA and to turn and processing
	handleGoodList(tmpdata);
	
	sendNotification(Facade_Mediator, AppFacade_BAG_PROXY_CHANGE, 0, BagMediator::CREATE_LIST);
}

void BagProxy::updateGoods(char* data)
{
	if (!data)
	{
		CCLog("error void BagProxy::updateGoods(char* data)");
	}

	std::list<GoodsInfo*> newarr;
	std::list<SCMD161_163_165_167Node>* tmpdata = (std::list<SCMD161_163_165_167Node>*)data;
	std::list<SCMD161_163_165_167Node>::iterator it;
	for (it = tmpdata->begin(); it != tmpdata->end(); it++)
	{
		SCMD161_163_165_167Node* goodInfo = &*it;
		GoodsInfo* old = _goodsList[goodInfo->a_sitGrid];
		if (!old)
		{
			continue;
		}
		if (old->id > 0 && goodInfo->b_id <= 0)
		{
			_noEmpty--;
		}
		else if (old->id <= 0 && goodInfo->b_id > 0)
		{
			_noEmpty++;
		}

		updateGoodList(goodInfo);
		newarr.push_back(_goodsList[goodInfo->a_sitGrid]);
	}
	sendNotification(Facade_Mediator, AppFacade_BAG_PROXY_CHANGE, (char*)&newarr, BagMediator::BAG_ITEM_UPDATE);

	// LH0714
// 	std::list<GoodsInfo*>::iterator iter = newarr.begin();
// 	for (;iter != newarr.end();iter++)
// 	{
// 		CC_SAFE_DELETE(*iter);
// 	}
	newarr.clear();// LH0714
	//			sendNotification(MainUIMediator.IS_BAG_FULL,getSpaceGridNum());
}

/**
* Update the items grid
* @param arr SCMD161Type array


* 
*/	
/*
		public function updateGoods(arr:Array):void{
			var newArr:Array = [];
			for each(var goodInfo:SCMD161_163_165_167Node in arr){
				var old:GoodsInfo = _goodsList[goodInfo.a_sitGrid.value];
				if(old.id >0 && goodInfo.b_id <=0){
					_noEmpty--;
				}
				else if(old.id <=0 && goodInfo.b_id >0){
					_noEmpty++;
				}
				updateGoodList(goodInfo);
				newArr.push(_goodsList[goodInfo.a_sitGrid.value]);
			}
			sendNotification(BagMediator.BAG_ITEM_UPDATE,newArr);
			sendNotification(MainUIMediator.IS_BAG_FULL,getSpaceGridNum());
		}
*/

void BagProxy::handleGoodList(std::list<SCMD161_163_165_167Node>* arr)
{
	_noEmpty = 0;
	std::list<SCMD161_163_165_167Node>::iterator it;
	for (it = arr->begin(); it != arr->end(); it++)
	{
		SCMD161_163_165_167Node* onedata = &*it;

		updateGoodList(onedata);

		if (onedata->c_goodId != 0)
		{
			_noEmpty++;
		}
	}
}

/**
* Update items
* 
*/		
void BagProxy::updateGoodList(SCMD161_163_165_167Node* goodInfo)
{
	GoodsInfo* info = new GoodsInfo();
	info->sitGrid = goodInfo->a_sitGrid;
	info->id = goodInfo->b_id;
	info->goodId = goodInfo->c_goodId;//prototype ID
	info->number = goodInfo->d_number;
	info->strengthen = goodInfo->e_superLv;
	info->stamina = goodInfo->f_stamina;
	info->wrist = goodInfo->g_wrist;
	info->intellect = goodInfo->h_intellect;
	//info->explain = 0;
	if (info->id != 0)//如果id为0，此位置为空，不需要初始化其他信息
	{
		GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(info->goodId);
		if (!goodBasic) return;
		info->name = goodBasic->goodName;
		info->type = goodBasic->type;
		info->equip_type = goodBasic->equip_type;
		info->quality = goodBasic->quality; 
		if (goodBasic->type == 3)
		{//fragments
			info->explain = GoodsToolTips::getExplain(goodBasic,false,info->number);
		}
		else if (g_pGoodsDynamicManager->getGoodsDynamic(info->id) != 0)
		{
			info->explain = GoodsToolTips::getGoodsTooltips(goodBasic, g_pGoodsDynamicManager->getGoodsDynamic(info->id));
		}
		else if (goodBasic->type == 2)//equipment
		{
			GoodsDynamic* dynamic = g_pGoodsDynamicManager->createDynamic(info, goodBasic);
			if (!dynamic)
			{
				cocos2d::CCLog("!dynamic   BagProxy::updateGoodList");
			}
			info->explain = GoodsToolTips::getGoodsTooltips(goodBasic, dynamic);
		}
		else
		{
			info->explain = GoodsToolTips::getDefaultExplain(goodBasic, info->id, 0);
		}
	}

	std::map<int32, GoodsInfo*>::iterator it = _goodsList.find(info->sitGrid);
	if (it != _goodsList.end())
	{
		GoodsInfo* infodelete = it->second;
		if (infodelete) 
		{
			//CC_SAFE_DELETE(infodelete->explain);
			CC_SAFE_DELETE(infodelete);
		}
		_goodsList.erase(it);
	}
	_goodsList.insert(make_pair(info->sitGrid, info));//以位置做索引
}


GoodsInfo* BagProxy::goodsInfo(int32 sitNum)
{
	std::map<int32, GoodsInfo*>::iterator it;
	if ((it = _goodsList.find(sitNum)) != _goodsList.end())
	{
		return it->second;
	}
	return 0;
}

/**
	*获取仓库空位置总数
	* @return int
	* 
	*/		
int32 BagProxy::getSpaceGridNum()
{
	return _goodsNumber - _noEmpty;
}

/**
* 设置物品的动态信息,并更新explain
* @param sitNum
*/
void BagProxy::setDynamicInfo( uint sitNum )
{
	GoodsInfo* info = goodsInfo( sitNum );
	GoodsDynamic* pDynamic = g_pGoodsDynamicManager->getGoodsDynamic(info->id);
	if( info && pDynamic )
	{
		info->explain = GoodsToolTips::getGoodsTooltips( g_pGoodsManager->getBasicGood( info->goodId ),
			pDynamic, 0 );

		struct Node
		{
			int id;
			int grid;
			int type;
		} node;
		node.id = info->id;
		node.grid = info->sitGrid;
		node.type = info->equip_type;
		sendNotification( Facade_Mediator, AppFacade_BAG_PROXY_CHANGE, (char*)&node, BagMediator::BAG_ITEM_TIP_UPDATE );
	}
}