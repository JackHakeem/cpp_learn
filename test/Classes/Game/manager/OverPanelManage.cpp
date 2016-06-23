#include "OverPanelManage.h"
#include "control/AppFacade.h"
#include "model/backpack/BagProxy.h"
#include "model/bank/BankProxy.h"
#include "view/backpack/components/BagGoods.h"
#include "view/bank/components/BankGoods.h"
#include "view/bank/components/BankView.h"
#include "events/GameDispatcher.h"
#include "manager/LayerManager.h"
#include "mvc/Facade.h"
#include "view/figure/FigureMediator.h"
#include "ViewManager.h"
#include "Message.h"
#include "model/com/GoodsDynamicManager.h"
#include "utils/ValuesUtil.h"

OverPanelManage* g_pOverPanelManage = 0;

OverPanelManage::OverPanelManage():_dispatcher(0)
{
	bagMediator = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
	bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);

	bankMediator = (BankMediator*)g_pFacade->retrieveMediator(AppFacade_BANK_PROXY_CHANGE);
	bankProxy = (BankProxy*)g_pFacade->retrieveProxy(AppFacade_BANK_PROXY_CHANGE);

	_dispatcher = GameDispatcher::getInstance();

	UseType = 0;
	sitGrid = 0;
}



/**
	*  
	* @ param sid where things are
	* @ param overName target window name
	* @ param locX target coordinates X
	* @ param locY target coordinates Y
	* @ param fromName source window name
	* 
	*/	
void OverPanelManage::goodsMove(int32 sid, int32 overName, float locX, float locY, int32 fromName, CCObject* other)
{	
	switch(overName)
	{
	case OVER_1_FIGURE:
		if(fromName==OVER_2_BAG)//Backpack internal mobile
		{
			putOnEquipment(sid,other);
		}
		break;
	case OVER_7_BAG_ITEM:
		if(fromName==OVER_2_BAG)//Backpack internal mobile
		{			
			moveGoods(locX, locY, sid);
		}
		else if (fromName == OVER_6_BANK)//From the warehouse drag. Come on
		{
			panelChange(1, sid);
		}
		else if (fromName == OVER_10_SHOP)
		{
				//		var goodsBasic:GoodsBasic =GoodsManager.getInstance().getBasicGood(sid);
				//		moveShopGoods(goodsBasic.goodId,goodsBasic.goodName,goodsBasic.price);			
		}
		else if (fromName == OVER_1_FIGURE)//Figure from equipment to drag
		{
		//putDownEquipment(other as uint, sid);
		}
		break;
	case OVER_2_BAG:
		break;
	case OVER_8_BANK_ITEM:
		if(fromName==OVER_6_BANK)//Warehouse internal mobile
		{			
			moveBankGoods(locX, locY, sid);
		}
		else if(fromName==OVER_2_BAG)//From the backpack drag. Come on
		{	
			panelChange(0, sid);
		}
		break;
	case OVER_6_BANK:
		break;
	case OVER_10_SHOP://The shop frame range
		panelChange(2, sid);       //Drag the shop panel backpack sell things
		break;
	default:
		break;
	}
}


/*
		public function goodsMove(sid:int, overName:String, locX:Number, locY:Number, fromName:String=null, other:Object=null):void
		{
			switch (overName)
			{
				case OverPaneName.OVER_1_FIGURE://目标：人物装备
					if(fromName==OverPaneName.OVER_2_BAG){	//从背包-->人物面板
						panelChange(2, sid);
					}
					break;
				case OverPaneName.OVER_7_BAG_ITEM:			//目标：背包窗格
					if(fromName==OverPaneName.OVER_2_BAG){			//背包内部移动
						moveGoods( locX, locY, sid);
					}else if(fromName==OverPaneName.OVER_6_BANK){	//从仓库拖拽过来
						panelChange(1, sid);
					}else if(fromName==OverPaneName.OVER_10_SHOP){
						var goodsBasic:GoodsBasic =GoodsManager.getInstance().getBasicGood(sid);
						moveShopGoods(goodsBasic.goodId,goodsBasic.goodName,goodsBasic.price);
					}else if(fromName==OverPaneName.OVER_1_FIGURE){	//从人物装备拖来
							putDownEquipment(other as uint, sid);
					}
					break;
				case OverPaneName.OVER_2_BAG://背包边框范围内，什么都不做
					break;
				case OverPaneName.OVER_8_BANK_ITEM:					//目标：仓库窗格
					if(fromName==OverPaneName.OVER_6_BANK){			//仓库内部移动
						moveBankGoods(locX, locY, sid);
					}else if(fromName==OverPaneName.OVER_2_BAG){	//从背包拖拽过来
						panelChange(0, sid);
					}
					break;
				case OverPaneName.OVER_6_BANK://仓库边框范围内
					break;
				case OverPaneName.OVER_10_SHOP://商店边框范围内  
					panelChange(2, sid);       //背包拖到商店面板卖出物品
					break;
				default:		
					//Alert.show(new GameError(GameError.DELETE_GOOD_WARM).message, "提示", 1, onDeleteOk, null, "确认", "取消",{sid:myGoods.sitGrid, num:myGoods.number});
					if(fromName==OverPaneName.OVER_2_BAG){	//从背包删除
						throwGoods(sid);
//						var num:uint = bagProxy.goodsInfo(sid).number;
//						Alert.show(new GameCodeMsg("C0020").message, "提示", 1, 
//							function ():void{throwGoods(sid, num)}, null, "确认", "取消");
					}else if(fromName==OverPaneName.OVER_6_BANK){
						panelChange(1, sid);
					}
					break;
			}
		}
		*/

/**
	* 移动物品 
	* @param id
	* @param locX
	* @param locY
	* @param oldsit
	* 

			private function moveGoods(locX:Number, locY:Number, oldsit:int):void
		{	
			if (locX < 1 || locX > 304 || locY < 1 || locY > 386)
			{
				return;
			}
			var goodDic:Dictionary=bagProxy.goodList;			
			var newsit:int = int(locY/43) * 6 + int(locX/43);
			if(newsit != oldsit && goodDic[newsit]!=null){
				_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.PACK_CHANGE, 
								{UseType:1, oldGrid:oldsit, newGrid:newsit}));
			}
		}
	*/

void OverPanelManage::moveGoods(float locX, float locY, int32 oldsit)
{
	/*
	if (locX < 1 || locX > 304 || locY < 1 || locY > 386)
	{
		return;
	}
	*/
	int32 newsit = -1;

	BagGoods* bagGoods = bagMediator->_bagView->getCurSelectedBagGoods(ccp(locX, locY));
	if (bagGoods)
		newsit = bagGoods->getTag();
	else
	{
		//本格ITEM和FRAME重现
		bagGoods = bagMediator->_bagView->m_pCurSelectedBagGoods;
		if (bagGoods)
			bagGoods->reShowItemAndFrame(true);
		return;
	}
	//

	if (bagProxy)
	{
		if (newsit != oldsit)
		{

			std::map<int32, GoodsInfo*>::iterator it;
			if ((it = bagProxy->_goodsList.find(newsit)) != bagProxy->_goodsList.end())
			{
				if (bagMediator && _dispatcher)
				{
					struct sdata
					{
						int32 UseType;
						int32 oldGrid;
						int32 newGrid;
					};
					sdata d;
					d.UseType = 1;
					d.oldGrid = oldsit;
					d.newGrid = newsit;
					_dispatcher->dispatchEvent(GameDispatcher::PACK_CHANGE, &d);
				}
				//_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.PACK_CHANGE, {UseType:1, oldGrid:oldsit, newGrid:newsit}));
			}
		}
		else
		{//This case ITEM and FRAME again
			bagGoods->reShowItemAndFrame(true);
		}	
	}
}

void OverPanelManage::moveBankGoods(float locX, float locY, int32 oldsit)
{
	/*
	if (locX < 1 || locX > 304 || locY < 1 || locY > 386)
	{
		return;
	}
	*/
	int32 newsit = -1;

	BankGoods* bankGoods = bankMediator->_bankView->getCurSelectedBankGoods(ccp(locX, locY));
	if (bankGoods)
		newsit = bankGoods->getTag();
	else
	{
		//本格ITEM和FRAME重现
		bankGoods = bankMediator->_bankView->m_pCurSelectedBankGoods;
		if (bankGoods)
			bankGoods->reShowItemAndFrame(true);
		return;
	}
	//

	if (bankProxy)
	{
		if (newsit != oldsit)
		{

			std::map<int32, GoodsInfo*>::iterator it;
			if ((it = bankProxy->_goodsList.find(newsit)) != bankProxy->_goodsList.end())
			{
				if (bankMediator)
				{
					struct sdata
					{
						int32 UseType;
						int32 oldGrid;
						int32 newGrid;
					};
					sdata d;
					d.UseType = 1;
					d.oldGrid = oldsit;
					d.newGrid = newsit;
					_dispatcher->dispatchEvent(GameDispatcher::BANK_CHANGE, (void*)&d);
				}
			}
		}
		else
		{//This case ITEM and FRAME again
			bankGoods->reShowItemAndFrame(true);
		}	
	}
}


/**
	*Panel to move between items
	* @param type 
	* @param sitNum
	* 
	*/		
void OverPanelManage::panelChange(uint32 type, uint32 siteNum)
{
	int param = 0;
	if (type == 0 || type == 2)
		param = GameDispatcher::PACK_CHANGE;
	else if (type == 1)
		param = GameDispatcher::BANK_CHANGE;
	else
		return;
	if (_dispatcher)
	{
		struct sdata
		{
			int32  UseType;
			uint32 type;
			uint32 sitNum;
		};
		sdata d;
		d.UseType = 2;
		d.type = type;
		d.sitNum = siteNum;
		_dispatcher->dispatchEvent(param, (void*)&d);
	}
}

#include "view/shop/ShopMediator.h"

void OverPanelManage::sellGoods(CCObject* pSender)
{
	struct sdata
	{
		int32 UseType;
		int32 sit;
	//	int32 goodid;
	};
	sdata d;
	d.UseType = 2;
	d.sit = sitGrid;
	ShopMediator* shopMediator = (ShopMediator*)g_pFacade->retrieveMediator(AppFacade_SHOP_PROXY_CHANGE);

	shopMediator->shopBuy(0, &d);

	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
}

void OverPanelManage::throwGoods(CCObject* pSender)
{
	struct sdata
	{
		int32 UseType;
		int32 sitGrid;
	};
	sdata d;
	d.UseType = UseType;
	d.sitGrid = sitGrid;

	_dispatcher->dispatchEvent(GameDispatcher::PACK_CHANGE, &d);

	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
}

void OverPanelManage::buttonBagToBank(CCObject* pSender)
{
	panelChange(0, sitGrid);

	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
}

void OverPanelManage::buttonBankToBag(CCObject* pSender)
{
	if (bankMediator)
		bankMediator->bankToBag(sitGrid);

	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
}

void OverPanelManage::putOnEquipment_forBtn(CCObject* pSender)
{
	int sid = sitGrid;
	FigureMediator * fm = (FigureMediator * )g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();

	if (!g_pFigureScrollView)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
		return;
	}
	int cnt = g_pFigureScrollView->currentScreen-1;
	while (cnt)
	{
		++iter;
		--cnt;
	}

	if (_pCurBagGoods&&(_pCurBagGoods->myInfo)&&(iter != list->end()))
	{
		if (_pCurBagGoods->myInfo->type != 2)
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("EOE3"),ccc3(244,12,12),1);
			LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
			return;
		}
		char career[32];
		sprintf(career,"CAR%d",iter->second.playerBaseInfo.career);
		if (!strstr(_pCurBagGoods->myInfo->explain.needCareer.c_str(),ValuesUtil::Instance()->getString(career).c_str())
			&& !strstr(_pCurBagGoods->myInfo->explain.needCareer.c_str(),ValuesUtil::Instance()->getString("ALLCAR").c_str()))
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("EOE1"),ccc3(244,12,12),1);
			//_pCurBagGoods->reShowItemAndFrame(true);这里不需要
			LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
			return;
		}
		if (_pCurBagGoods->myInfo->explain.needLevel > iter->second.playerBaseInfo._lev)
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("EOE2"),ccc3(244,12,12),1);
			LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
			return;
		}
	}


	uint32 account = 0;
	if (iter != list->end())
	{
		account = iter->first.id;
	}
	if (fm)
	{
		fm->sendOnClotheRequest(account,sid);
	}

	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
}

void OverPanelManage::putOnEquipment(int sid,CCObject* pSender)
{
	FigureMediator * fm = (FigureMediator * )g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();

	if (!g_pFigureScrollView)
	{
		return;
	}
	int cnt = g_pFigureScrollView->currentScreen-1;
	while (cnt)
	{
		++iter;
		--cnt;
	}

	BagGoods * pBagGoods = (BagGoods *)pSender;
	if (pBagGoods&&(pBagGoods->myInfo)&&(iter != list->end()))
	{
		if (pBagGoods->myInfo->type != 2)
		{
			pBagGoods->reShowItemAndFrame(true);
			Message::Instance()->show(ValuesUtil::Instance()->getString("EOE3"),ccc3(244,12,12),1);
			return;
		}		
		char career[32];
		sprintf(career,"CAR%d",iter->second.playerBaseInfo.career);
		if (!strstr(pBagGoods->myInfo->explain.needCareer.c_str(),ValuesUtil::Instance()->getString(career).c_str())
			&& !strstr(pBagGoods->myInfo->explain.needCareer.c_str(),ValuesUtil::Instance()->getString("ALLCAR").c_str()))
		{
			pBagGoods->reShowItemAndFrame(true);
			Message::Instance()->show(ValuesUtil::Instance()->getString("EOE1"),ccc3(244,12,12),1);
			return;
		}
		if (pBagGoods->myInfo->explain.needLevel > iter->second.playerBaseInfo._lev)
		{
			pBagGoods->reShowItemAndFrame(true);
			Message::Instance()->show(ValuesUtil::Instance()->getString("EOE2"),ccc3(244,12,12),1);
			return;
		}
	}

	uint32 account = 0;
	if (iter != list->end())
	{
		account = iter->first.id;
	}
	if (fm)
	{
		fm->sendOnClotheRequest(account,sid);
	}
}

void OverPanelManage::putDownEquipment(CCObject* pSender)
{
	FigureMediator * fm = (FigureMediator * )g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);	
	//std::map<int ,PlayerInfoVo>* list = RoleManage::Instance()->mercList();
	//std::map<int, PlayerInfoVo>::iterator iter = list->begin();
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* list = RoleManage::Instance()->mercListEx();  // LH20121019listorder
	std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator iter = list->begin();
	uint32 account = 0;
	if (!g_pFigureScrollView)
	{
		return;
	}
	int cnt = g_pFigureScrollView->currentScreen-1;
	while (cnt)
	{
		++iter;
		--cnt;
	}
	if (iter != list->end())
	{
		account = iter->first.id;
	}
	if (!fm)
	{
		return;
	}
	if (!bagProxy)
	{
		return;
	}
	if (bagProxy->getSpaceGridNum()<=0)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("EQU001"),ccc3(240,44,22),1);
		return;
	}
	int totalGrid = bagProxy->_goodsNumber;
	int emptyGrid = 0;
	for (emptyGrid =0;emptyGrid<totalGrid;emptyGrid++)
	{
		if (!bagProxy->_goodsList[emptyGrid]->id)
		{
			break;
		}
	}
	
	fm->sendDownClotheRequest(account,this->sitGrid,emptyGrid);
	//
	LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
}
