#include "ShopMediator.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "view/shop/components/ShopView.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "model/backpack/BagProxy.h"
#include "socket/command/c17/CCMD178.h"
#include "socket/command/c17/CCMD17A.h"
#include "socket/network/GameServerSocket.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/GoodsManager.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/player/RoleManage.h"
#include "view/backpack/components/BagGoods.h"
#include "view/backpack/BagMediator.h"
#include "manager/LangManager.h"
#include "Confirm.h"
#include "model/shop/ItemRiseInfo.h"
#include "manager/ViewManager.h"

const uint8 EQUIPMENT_BASIC_STRENGTHEN_FEE			= 100;  // 强化初始费用
const uint8 STREN_LEVEL_RADIX						= 10;	// 级别
const float EQUIPMENT_STRENGTHEN_FAIL_RETURN_PERC = 0.7f;

ShopMediator::ShopMediator()
{
	_shopView = 0;
	_dispatcher = 0;

	e_param_sit = 0;//临时缓存物品位置
	e_param_sellvalue = 0;//临时缓存要卖出的强化价格

	_dispatcher = GameDispatcher::getInstance();
	_dispatcher->addEventListener(PopEventName::SHOW_UI_SHOP, this, callfuncND_selector(ShopMediator::shopPopHandler) );
	_dispatcher->addEventListener(GameDispatcher::SHOP_VIEW_CLICK, this, callfuncND_selector(ShopMediator::shopBuy)); 
}

ShopMediator::~ShopMediator()
{}

void ShopMediator::shopPopHandler(CCNode* p, void* e)
{
	int32 e_param = *((int32*)e);
	
	_shopId = e_param;
	//ModuleLoaderManage.getInstance().load(ResourceName.SHOP_SKIN_PATH, LoadLevel.HIGH, openShopView);
	openShopView();
}


void ShopMediator::openShopView()
{
	if (!_shopView)
	{
		_shopView = new ShopView();
		ViewManager::getInstance()->_shopView = _shopView;
		_shopView->init();
	}
	if (_shopView->getisPop())
	{
		_shopView->close();
	}
	else
	{
		_shopView->setisPop(true);

		_shopView->release(); //LH20120108

		_shopView->createList(_shopId);
		_shopId = 0;
	}
}

void ShopMediator::shopBuy(CCNode* p, void* e)
{
	if (!e) 
		return;

	int32 e_param_UseType = *((int32*)e);

	switch (e_param_UseType)
	{
	case 1:
		{
			struct sdata
			{
				int32 UseType;
				int32 id;
				std::string name;
				int32 price;
				int32 shopid;
			};
			sdata* e_param = (sdata*)e;
			//Alert.show("你确定要购买："+e.param.name+" ？","",1, onBuyGridAlert, null, "确定", "取消", e.param, 1);
			onBuyGridAlert(e_param->id);
		}
		break;
	case 2:
		{
			struct sdata
			{
				int32 UseType;
				int32 sit;
			//	int32 goodid;
			};
			sdata* e_param = (sdata*)e;

			BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
			if (!_bagProxy) 
				break;
			GoodsInfo* goodsInfo = _bagProxy->goodsInfo(e_param->sit);
			if (goodsInfo)
			{
				BagMediator* bagMediator = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
				BagGoods* bagGoods = 0;
				if ( bagMediator &&  bagMediator->_bagView)
				{
					bagGoods = bagMediator->_bagView->m_pCurSelectedBagGoods;
					if (!bagGoods)
						break;
				}

				//
				//KC1011
				if (goodsInfo->strengthen >= 1)
				{
					if (bagGoods)
						bagGoods->reShowItemAndFrame(true);
					//LangManager::msgShow("SHOP003");
					e_param_sit = e_param->sit;
					
					//show ui
					GoodsBasic* pGoodsBasic = g_pGoodsManager->getBasicGood(goodsInfo->goodId);
					if (!pGoodsBasic)
						return;
					int nStrenVal = ItemRiseInfo::Instance()->getGrowup(pGoodsBasic->quality, pGoodsBasic->equip_type, pGoodsBasic->item_type);
					if (nStrenVal == -1)
						return;

					int n = goodsInfo->strengthen;
					int sellvalue = ceil((EQUIPMENT_BASIC_STRENGTHEN_FEE   +  (n-1) * STREN_LEVEL_RADIX /2 + (n-1) * (n + 1) * nStrenVal /3  )* 
						n * 
						EQUIPMENT_STRENGTHEN_FAIL_RETURN_PERC)+pGoodsBasic->sell_price;
					e_param_sellvalue = sellvalue;//临时缓存要卖出的强化价格
					
					char str[128];
					sprintf(str, ValuesUtil::Instance()->getString("SHOP004").c_str(), pGoodsBasic->goodName.c_str(), n, sellvalue);
					
					Confirm* pConfirm = new Confirm();
					pConfirm->initWithParam(str, this, menu_selector(ShopMediator::okSellItem),menu_selector(ShopMediator::okSellItemCancel));
					LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
					pConfirm->release();
				}
				else if (RoleManage::Instance()->_accountInfo.silver() + bagGoods->myInfo->number*bagGoods->myInfo->explain.s_sell_price > 
					RoleManage::Instance()->_accountInfo._silverLim) 
				{
					if (bagGoods)
						bagGoods->reShowItemAndFrame(true);
					LangManager::msgShow("SHOP002");
				}
				else if (goodsInfo->quality >= 4)
				{
					e_param_sit = e_param->sit;

					Confirm* pConfirm = new Confirm();
					pConfirm->initWithParam(ValuesUtil::Instance()->getString("SHOP005").c_str(), this, menu_selector(ShopMediator::okSellItemQuality4),menu_selector(ShopMediator::okSellItemCancel));
					LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
					pConfirm->release();
				}
				else			
				{
					onSellGridAlert(e_param->sit);
				}
			}
		}
		break;
	default:
		break;
	}
}

void ShopMediator::okSellItemQuality4(CCObject* pSender)
{
	onSellGridAlert(e_param_sit);

	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void ShopMediator::okSellItem(CCObject* pSender)
{
	if (RoleManage::Instance()->_accountInfo.silver() + e_param_sellvalue > RoleManage::Instance()->_accountInfo._silverLim) 
	{
		LangManager::msgShow("SHOP002");
	}
	else
		onSellGridAlert(e_param_sit);

	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

void ShopMediator::okSellItemCancel(CCObject* pSender)
{
	BagMediator* bagMediator = (BagMediator*)g_pFacade->retrieveMediator(AppFacade_BAG_PROXY_CHANGE);
	BagGoods* bagGoods = 0;
	if ( bagMediator &&  bagMediator->_bagView)
	{
		bagGoods = bagMediator->_bagView->m_pCurSelectedBagGoods;
		if (bagGoods)
		{
			bagGoods->reShowItemAndFrame(true);
		}
	}

	CCNode* pSell = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame);
	if (pSell)
		pSell->removeFromParentAndCleanup(true);
}

/*
				case 2://goodid
					var goodsInfo:GoodsInfo = _bagProxy.goodsInfo(e.param.sit);
					if(goodsInfo != null){
						var goods:GoodsBasic = GoodsManager.getInstance().getBasicGood(goodsInfo.goodId);
						if(goodsInfo.strengthen >=1){
							MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "S254");
						}
						else if(RoleManage.getInstance().accountInfo.silver + goods.sell_price*goodsInfo.number
							>RoleManage.getInstance().accountInfo.silverLim)
						{
							MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "S253");
						}
						else{
							Alert.show("你确定要卖出："+goods.goodName+" ？","",1, onSellGridAlert, null, "确定", "取消", e.param, 1);
						}
					}
					break;
					*/

void ShopMediator::onSellGridAlert(int32 sit)
{
	CCMD17A* sender = new CCMD17A();
	if (sender)
	{
		sender->a_shopid = static_cast<int16>(_shopView->_shopId);
		sender->b_sit = static_cast<int16>(sit);
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(sender);
	}
	SAFE_DELETE(sender);
}
/*
		private function onSellGridAlert(param:Object):void{
			var sender:CCMD17A = new CCMD17A();
			sender.a_shopid = new Int16(_shopView.shopID());
			sender.b_sit = new int(param.sit)
			_wSocket.sendMessage(SocketCMDConst.CMSG_WORLD_ITEM_SELL,sender);
		}

*/
void ShopMediator::onBuyGridAlert(int32 id)
{
	BagProxy* _bagProxy = (BagProxy*)g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	if (!_bagProxy) 
		return;
	if (_bagProxy->getSpaceGridNum() == 0)
	{
		//Message.show("背包已满，无法购买物品");
		return;
	}

	int32 shopid = _shopView->_shopId;
	int32 itemid = id;

	CCMD178* sender = new CCMD178();
	if (sender)
	{
		sender->a_shopid = static_cast<int16>(shopid);
		sender->b_goodid = static_cast<int16>(itemid);
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(sender);

		LayerManager::loadingPic->socketWait_old( WMSG_WORLD_BAG_ITEM_UPDATE );
	}
	SAFE_DELETE(sender);
}


/*
		private function shopBuy (e:ParamEvent):void
		{
			switch (e.param.UseType)
			{
				case 1:
					Alert.show("你确定要购买："+e.param.name+" ？","",1, onBuyGridAlert, null, "确定", "取消", e.param, 1);
					break;
				case 2://goodid
					var goodsInfo:GoodsInfo = _bagProxy.goodsInfo(e.param.sit);
					if(goodsInfo != null){
						var goods:GoodsBasic = GoodsManager.getInstance().getBasicGood(goodsInfo.goodId);
						if(goodsInfo.strengthen >=1){
							MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "S254");
						}
						else if(RoleManage.getInstance().accountInfo.silver + goods.sell_price*goodsInfo.number
							>RoleManage.getInstance().accountInfo.silverLim)
						{
							MsgManage.getInstance().showMsg(MsgManage.SYSTEM_MSG, "S253");
						}
						else{
							Alert.show("你确定要卖出："+goods.goodName+" ？","",1, onSellGridAlert, null, "确定", "取消", e.param, 1);
						}
					}
					break;
			}
		}
		*/
