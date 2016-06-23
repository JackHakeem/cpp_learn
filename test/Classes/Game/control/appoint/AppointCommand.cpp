#include "AppointCommand.h"
#include "socket/command/s1e/SCMD1E1.h"
#include "socket/command/s1e/SCMD1E3.h"
#include "socket/command/s1e/SCMD1E6.h"
#include "socket/command/s1d/SCMD1DD.h"
#include "model/appoint/vo/AppointVo.h"
#include "model/appoint/AppointManager.h"
#include "view/appoint/AppointMediator.h"
#include "../AppFacade.h"
#include "mvc/Facade.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "model/backpack/GoodsManager.h"
#include "model/com/GoodsToolTips.h"
#include "model/appoint/vo/GoodsVo.h"
#include "view/appoint/components/GoodsView.h"
#include "model/player/RoleManage.h"
#include "model/appoint/vo/AppointBlessVo.h"
#include "manager/GlobalManage.h"


void AppointCommand::execute( int32 command, char* data )
{
	switch (command)
	{
	case INIT_INFO:
		initInfo(data);
		break;

	case APPOINT_RESULT:
		appointResult(data);
		break;

	case RECEIVE_RESULT:
		receiveResult(data);
		break;

	case BLESS_RESULT:
		blessResult(data);
		break;
	}
}

void AppointCommand::initInfo( char *pData )
{
	SCMD1E1 *pSCMD1E1 = (SCMD1E1 *)pData;
	if(!pSCMD1E1)
	{
		return;
	}
	AppointManager *pAppointManager = AppointManager::Instance();
	if(!pAppointManager)
	{
		return;
	}
	AppointVo *traderInfo2 = pAppointManager->getTraderVoByLev(1, 0);
	traderInfo2->freeNum = pSCMD1E1->a_freeNum;
	traderInfo2->bitNum = pSCMD1E1->c_cloakTrader;
	sendNotification(Facade_Mediator, AppFacade_APPOINT_MEDIATOR, (char *) traderInfo2, AppointMediator::UPDATE_TRADER_INFO);

	AppointVo *traderInfo = pAppointManager->getTraderVoByLev(0,  0);
	traderInfo->freeNum = pSCMD1E1->a_freeNum;
	traderInfo->bitNum = pSCMD1E1->b_ringTrader;
	sendNotification(Facade_Mediator, AppFacade_APPOINT_MEDIATOR, (char *) traderInfo, AppointMediator::UPDATE_TRADER_INFO);

	pAppointManager->_goodsArr.clear();
	std::list<int16>::iterator it;
	if(!g_pGoodsManager)
	{
		return;
	}
	for(it = pSCMD1E1->d_goods.begin(); it != pSCMD1E1->d_goods.end(); ++ it)
	{
		int id = *it;
		GoodsBasic *pGoodsBasic = g_pGoodsManager->getBasicGood(id);
		//std::string info = GoodsToolTips::getExplain(pGoodsBasic, false);
		GoodsVo *pGoodsVo = new GoodsVo();
		pGoodsVo->id = id;
		//pGoodsVo->info = info;
		pGoodsVo->quality = pGoodsBasic->quality;
		pGoodsVo->sellPrice = pGoodsBasic->sell_price;
		char pIcon[50];
		//sprintf(pIcon, "goods/%d.png", id);
		sprintf(pIcon, "assets/icon/goods/%d.png", id);
		pGoodsVo->icon = pIcon;
		pAppointManager->_goodsArr.push_back(new GoodsView(pGoodsVo));
	}
	//sortGoods(goods);
	//20120808
	//Doyang
	sortGoods();
	sendNotification(Facade_Mediator, AppFacade_APPOINT_MEDIATOR, NULL, AppointMediator::INIT_FINISHI);

}

void AppointCommand::appointResult( char *pData )
{
	SCMD1E3 *pSCMD1E3 = (SCMD1E3 *) pData;
	if(!pSCMD1E3)
	{
		return;
	}

	AppointManager *pAppointManager = AppointManager::Instance();
	if(!pAppointManager)
	{
		return;
	}
	AppointVo *traderInfo = pAppointManager->getTraderVoByLev(pSCMD1E3->b_traderType,  pSCMD1E3->d_selected);
	traderInfo->freeNum = pSCMD1E3->a_freeNum;
	traderInfo->bitNum = pSCMD1E3->c_trader;
	sendNotification(Facade_Mediator, AppFacade_APPOINT_MEDIATOR, (char *) traderInfo, AppointMediator::UPDATE_TRADER_INFO);

	int id = pSCMD1E3->a_goodsId;
	if(!g_pGoodsManager)
	{
		return;
	}
	GoodsBasic *goodsBasic = g_pGoodsManager->getBasicGood(id);
	if(!goodsBasic)
	{
		return;
	}
	//stri info:String = GoodsToolTips.getExplain(goodsBasic);
	GoodsVo *vo = new GoodsVo();
	vo->id = id;
	//vo->info = info;
	vo->quality = goodsBasic->quality;
	vo->sellPrice = goodsBasic->sell_price;
	char pIcon[50];
	//sprintf(pIcon, "goods/%d.png", id);
	sprintf(pIcon, "assets/icon/goods/%d.png", id);
	vo->icon = pIcon;
	pAppointManager->_goodsArr.push_back(new GoodsView(vo));
	//sortGoods(goods);
	//20120808
	//Doyang
	sortGoods();
}

void AppointCommand::receiveResult( char *pData )
{
	SCMD1E6 *pSCMD1E6 = (SCMD1E6 *) pData;
	if(!pSCMD1E6)
	{
		return;
	}

	AppointManager *pAppointManager = AppointManager::Instance();
	if(!pAppointManager)
	{
		return;
	}
	std::list<GoodsView *>::iterator it;
	for(it = pAppointManager->_goodsArr.begin(); it != pAppointManager->_goodsArr.end(); ++it)
	{
		GoodsView *pGoodsView = (GoodsView *) *it;
		if(!pGoodsView)
		{
			continue;
		}

		GoodsVo *pGoodsVo = pGoodsView->goodsVo;
		if(pGoodsVo->id == pSCMD1E6->a_goodsId)
		{
			pAppointManager->_goodsArr.erase(it);
			pGoodsView->dispose();
			break;
		}
	}
	//sortGoods(goods);

	//20120808
	//Doyang
	sortGoods();
}

void AppointCommand::blessResult( char *pData )
{
	SCMD1DD *pSCMD1DD = (SCMD1DD *) pData;
	if(!pSCMD1DD)
	{
		return;
	}

	AppointManager *pAppointManager = AppointManager::Instance();
	if(!pAppointManager)
	{
		return;
	}
	pAppointManager->setBlessValue(pSCMD1DD->a_blessValue);
	pAppointManager->setBlessTotal(pSCMD1DD->b_blessTotal);
	setExchangeType(pSCMD1DD->a_blessValue);
}

void AppointCommand::setExchangeType( int value )
{
	AppointManager *pAppointManager = AppointManager::Instance();
	if(!pAppointManager)
	{
		return;
	}
	int lev = RoleManage::Instance()->roleLev();

	int type = 0;
	std::list<AppointBlessVo *> &blessList = pAppointManager->getAppointBlessArr();
	std::list<AppointBlessVo *>::iterator it;
	for(it = blessList.begin(); it != blessList.end(); ++ it)
	{
		AppointBlessVo *pBlessVo = (AppointBlessVo *) *it;
		if(!pBlessVo)
		{
			continue;
		}

		if(lev >= pBlessVo->crystalLev)
		{
			type = 0;
			if(value >= pBlessVo->blessValue)
			{
				type = 1;
			}
		}
	}
	g_pGlobalManage->_exchangeType = type;
}

void AppointCommand::sortGoods()
{
	AppointMediator *pAppointMediator = (AppointMediator *)g_pFacade->retrieveMediator(AppFacade_APPOINT_MEDIATOR);
	if(pAppointMediator && pAppointMediator->_pAppointView)
	{
		pAppointMediator->_pAppointView->drawGoods();
	}
}

