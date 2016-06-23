#include "SpecialItemAddAction.h"
#include "manager/PopManage.h"
#include "events/GameDispatcher.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "model/backpack/GoodsManager.h"
#include "model/backpack/BagProxy.h"
#include "model/bank/BankProxy.h"
#include "socket/network/GameServerSocket.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/figure/EquipmentManager.h"
#include "socket/command/c17/CCMD170.h"
#include "model/newhand/NewhandManager.h"
#include "manager/ViewManager.h"
#include "view/backpack/BagMediator.h"
#include "manager/LangManager.h"
#include "NewEAlert.h"
#include "model/newhand/vo/NewhandConst.h"
#include "model/newhand/vo/TestNewhand.h"

SpecialItemAddAction::SpecialItemAddAction()
{
	_dispatcher = 0;
	_dispatcher = GameDispatcher::getInstance();
	_param_goodId = 0;
	
}

bool SpecialItemAddAction::init(SCMD16D* param)
{
	a_from = param->a_from;
	b_goodsId = param->b_goodsId;
	c_num = param->c_num;
	d_sitGrid = param->d_sitGrid;

	return true;
}

SpecialItemAddAction::~SpecialItemAddAction()
{

}

void SpecialItemAddAction::doAction()
{
	int goodsId = b_goodsId;
	GoodsBasic* goodBasic = g_pGoodsManager->getBasicGood(goodsId);

	bool isCanEquit = false;
	int32 mercId = 0;

	if (!g_pPopManage->isViewPop(PopEventName::BAG))//背包没有打开
	{
		if (RoleManage::Instance()->roleLev() && goodBasic && goodBasic->type == 2)//是装备类型，水晶小于20级
		{
			PlayerInfoVo* roleInfo = RoleManage::Instance()->roleInfo();
			mercId = roleInfo->playerBaseInfo.id;
			isCanEquit = checkCanEquip(roleInfo, goodBasic);
			if(!isCanEquit)
			{
				//std::map<int, PlayerInfoVo>* dic = RoleManage::Instance()->mercList();
				//std::map<int, PlayerInfoVo>::iterator it = dic->begin();
				std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>* dic = RoleManage::Instance()->mercListEx();  // LH20121019listorder
				std::map<RoleManage::MercKeyIndex ,PlayerInfoVo>::iterator it = dic->begin();
				for (it ; it != dic->end(); it++)
				{
					PlayerInfoVo* info = &it->second;
					isCanEquit = checkCanEquip(info, goodBasic);
					mercId = info->playerBaseInfo.id;
					if(isCanEquit) break;
				}
			}
		}
		if(isCanEquit)//能装备，直接装备，再提示（先斩后奏）
		{
			NewhandManager::Instance()->_isGetEquipment = true;

			autoPutOnEquipment(mercId, d_sitGrid);
			//NewEAlert::showAutoEquip(goodBasic, mercId, d_sitGrid );

			std::string title = ValuesUtil::Instance()->getString("BAG006");
			std::string content = ValuesUtil::Instance()->getString("BAG007");
			std::string btnName = ValuesUtil::Instance()->getString("BAG008");
			char pic_url[100];
			//sprintf(pic_url, "goods/%d.png", goodBasic->goodId);
			sprintf(pic_url, "assets/icon/goods/%d.png", goodBasic->goodId);
			NewEAlert::show(title, content, btnName, pic_url, 1 , this , menu_selector(SpecialItemAddAction::equipOnCallback));

			//if(NewhandManager::Instance()->_nextEventId == NewhandConst::EVENT_OPEN_GIFT)
			if((!NewhandManager::Instance()->_nextEventIdList.empty()) && (NewhandManager::Instance()->_nextEventIdList.front() == NewhandConst::EVENT_OPEN_GIFT))
			{
				/*struct Data
				{
					string type;
					int id;
				};
				Data data;
				data.type = "evt";
				data.id = NewhandConst::EVENT_OPEN_GIFT;*/
				//Doyang 20120712
				TestNewhand *pTestNewhand = new TestNewhand("evt", NULL, NewhandConst::EVENT_OPEN_GIFT);
				GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TEST_NEW_HAND, 
					pTestNewhand);
				CC_SAFE_DELETE(pTestNewhand);
			}
		}//不能装备，飞下去的效果
		else
		{
			int fromType = a_from;
			if(fromType==3 || fromType==2 || fromType==8 ||fromType==12 ||fromType==6 || fromType==21)
			{
				if(ViewManager::getInstance()->mainNavigate){
					//ViewManager::getInstance()->mainNavigate->showNewItemEffect(goodsId);
				}
			}
			if(goodsId ==1041 || goodsId ==1042 || goodsId ==1043 || goodsId ==1044)//新手礼包，搞特例
			{
				std::string content = ValuesUtil::Instance()->getString("BAG010");
				std::string title = ValuesUtil::Instance()->getString("COM001");
				std::string btnInfo = ValuesUtil::Instance()->getString("COM002");
				_param_goodId = goodsId;
				NewEAlert::show(title, content, btnInfo, "goods/1041.png",
					1, this, menu_selector(SpecialItemAddAction::openGoodsById), (char*)&_param_goodId, true);
			}
		} 
	}
	else
	{
		if (goodBasic)
		{
			char out[200];
			sprintf(out, ValuesUtil::Instance()->getString("BAG005").c_str(), goodBasic->goodName.c_str());
			LangManager::msgStr( out );		
		}
	}
}


/**
	* 判断能否自动装备   
	* @param info
	* @param goodBasic
	* @return 
	*/		
bool SpecialItemAddAction::checkCanEquip(PlayerInfoVo* info, GoodsBasic* goodBasic)
{
	bool ret = false;
	if((info->playerBaseInfo.career & goodBasic->career_id) && (info->playerBaseInfo.lev() >= goodBasic->level))
	{
		EquipmentVo* eqVo = EquipmentManager::Instance()->getEquipment(info->playerBaseInfo.id);
		if(!eqVo){
			ret = true;
		}
		else
		{
			GoodsInfo* eqInfo = eqVo->getIndex(goodBasic->equip_type);
			if(!eqInfo || eqInfo->id==0 ||eqInfo->quality < goodBasic->quality){
				ret = true;
			} 
		}
	}
	return ret;
}

/**
	*自动穿上装备 
	* @param mercId
	* @param sitGrid
	*/		
void SpecialItemAddAction::autoPutOnEquipment(int mercId, int sitNum)
{
	CCMD170 * c = new CCMD170();
	if (c)
	{
		c->a_figureId = mercId;
		c->b_sitGrid = (uint8)sitNum;
		GameServerSocket * pSocket = GameServerSocket::getInstance();
		if (pSocket)
		{
			pSocket->sendMessage(c);		
		}
		CC_SAFE_DELETE(c); // LH0712LEAK
	}
}

//根据原型id打开物品（新手阶段自动打开礼包）
void SpecialItemAddAction::openGoodsById(CCObject* pSender)
{	
	int id = ((CCNode *)pSender)->getTag();
	g_pFacade->sendNotification(Facade_Mediator, AppFacade_BAG_PROXY_CHANGE, (char*)&id, BagMediator::OPEN_ID_GOOD);

	//close
	NewEAlert* oldTar = (NewEAlert*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert);
	if (oldTar)
	{
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_NewEAlert, true);
	}
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::NEW_ALERT_CLOSE, NULL);
}

void SpecialItemAddAction::equipOnCallback(CCObject * pSender)
{
	NewEAlert* oldTar = (NewEAlert*)LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert);
	if (oldTar)
	{
		oldTar->clickClose(0);
	}

	int differ = NewhandManager::Instance()->_deltaAttacPoint;
	if (NewhandManager::Instance()->_pInfoVo)
	{
		char path[128] = {0};
		if (differ > 0)
		{
			sprintf(path , ValuesUtil::Instance()->getString("ADD0010").c_str() , NewhandManager::Instance()->_pInfoVo->playerBaseInfo.name.c_str() , differ);
			Message::Instance()->show(path , ccc3(255,215,0) , 2);
		} 
		else if (differ < 0)
		{
			sprintf(path , ValuesUtil::Instance()->getString("ADD0011").c_str() , NewhandManager::Instance()->_pInfoVo->playerBaseInfo.name.c_str() , (-1) * differ);
			Message::Instance()->show(path , ccc3(233,12,233), 2);
		}
	}
	//
	NewhandManager::Instance()->_deltaAttacPoint = 0;
	NewhandManager::Instance()->_pInfoVo = 0;
	NewhandManager::Instance()->_isGetEquipment = false;
}
