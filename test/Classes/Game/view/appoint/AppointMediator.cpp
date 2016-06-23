#include "AppointMediator.h"
#include "control/appoint/AppointCommand.h"
#include "model/appoint/AppointManager.h"
#include "manager/GlobalManage.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "model/player/RoleManage.h"
#include "manager/LangManager.h"
#include "model/player/vo/AccountInfoVo.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "manager/ViewManager.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c1e/CCMD1E0.h"
#include "manager/CDManage.h"
#include "socket/command/c1e/CCMD1E2.h"
#include "socket/command/c1e/CCMD1E5.h"
#include "socket/command/c1e/CCMD1E4.h"
#include "mvc/Facade.h"
#include "model/backpack/BagProxy.h"
#include "control/AppFacade.h"
#include "socket/command/c1d/CCMD1DC.h"
#include "model/backpack/GoodsManager.h"
#include "model/backpack/vo/GoodsBasic.h"
#include "utils/ValuesUtil.h"

AppointMediator::AppointMediator()
{
	_pAppointView = NULL;
	GameDispatcher *pGameDispatcher = GameDispatcher::getInstance();
	if(pGameDispatcher)
	{
		pGameDispatcher->addEventListener(PopEventName::SHOW_UI_APPOINT, this, callfuncND_selector(AppointMediator::popHandler));
		pGameDispatcher->addEventListener(PopEventName::SHOW_UI_APPOINT_BLESS, this, callfuncND_selector(AppointMediator::openAppointBlessView));
		pGameDispatcher->addEventListener(GameDispatcher::BLESS_EXCHANGE, this, callfuncND_selector(AppointMediator::exchangeHandler));
		pGameDispatcher->addEventListener(GameDispatcher::APPOINT_BLESS_EXCHANGE, this, callfuncND_selector(AppointMediator::appointBlessExchange));
	}

	//startSocketListener();		//������Ա�ϵͳ�����
}

void AppointMediator::getAppointInfo( SCMD1E1 *pData )
{
	/*if(!_appointView) return;*/
	sendNotification(Facade_Command, AppFacade_APPOINT_COMMAND, (char *) pData, AppointCommand::INIT_INFO);
}

void AppointMediator::getAppointResult( SCMD1E3 *pData )
{
	/*if(!_appointView) return;*/
	sendNotification(Facade_Command, AppFacade_APPOINT_COMMAND, (char *) pData, AppointCommand::APPOINT_RESULT);
}

void AppointMediator::getAppointGoods( SCMD1E6 *pData )
{
	/*if(!_appointView) return;*/
	sendNotification(Facade_Command, AppFacade_APPOINT_COMMAND, (char *) pData, AppointCommand::RECEIVE_RESULT);
}

void AppointMediator::getAppointBlessInfo( SCMD1DD *pData )
{
	/*if(!_appointView) return;*/
	sendNotification(Facade_Command, AppFacade_APPOINT_COMMAND, (char *) pData, AppointCommand::BLESS_RESULT);
}

void AppointMediator::getExchangeResult( SCMD1DB *pData )
{
	if(!pData)
		return;

	int type = pData->b_type;
	int id = pData->a_id;

	if(type == 1)
	{
		GoodsBasic *pGoods = g_pGoodsManager->getBasicGood(id);
		if(pGoods)
		{
			char pChar[128];
			sprintf(pChar, ValuesUtil::Instance()->getString("APT009").c_str(), pGoods->goodName.c_str());
			LangManager::msgStr(pChar);
		}
	}
	else
	{
		LangManager::msgShow("APT010");
	}
}

void AppointMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case INIT_FINISHI:
		initFinish();
		break;

	case UPDATE_TRADER_INFO:
		if(_pAppointView)
		{
			AppointVo *pAppointVo = (AppointVo *) data;
			if(pAppointVo)
			{
				_pAppointView->setCurTraderInfo(pAppointVo);
			}
		}
		break;
	}
}

void AppointMediator::initFinish()
{
}

void AppointMediator::appointBlessExchange(CCNode *pNode, void *pData)
{
	if(!_pAppointView || !g_pGlobalManage)
	{
		return;
	}
	int type = g_pGlobalManage->_exchangeType;
	if(type == 1)
	{
		_pAppointView->startFlasher();
	}
	else
	{
		_pAppointView->stopFlasher();
	}
}

void AppointMediator::popHandler( CCNode *pNode, void *pData )
{
	if(!RoleManage::Instance()->accountInfo())
	{
		return;
	}

	openAppointView();
}

void AppointMediator::openAppointBlessView( CCNode *pNode, void *pData )
{

}

void AppointMediator::openAppointView()
{
	if(!_pAppointView){
		_pAppointView = new AppointView();
		//������Ա��Ƿ����
		updateGoldAppoint(NULL, NULL);
		//����ˮ����ͼ���
		startViewListener();
		ViewManager::getInstance()->_appointView = _pAppointView;
	}
	_pAppointView->setisPop(!_pAppointView->getisPop());
	if(_pAppointView->getisPop()){	//�����ʼ����Ϣ
		CCMD1E0 *pPacket = new CCMD1E0();
		GameServerSocket::getInstance()->sendMessage(pPacket);
		CC_SAFE_DELETE(pPacket);

		bool isCrystalOpen = false;
		if(ViewManager::getInstance()->mainNavigate)
		{
			isCrystalOpen = ViewManager::getInstance()->mainNavigate->_isCrystalOpen;
		}

		AppointManager *pAppointManager = AppointManager::Instance();
		if(!pAppointManager)
		{
			return;
		}

		_pAppointView->updateBlessInfo(isCrystalOpen, 
			pAppointManager->getBlessValue(),
			pAppointManager->getBlessTotal());
		
		//Doyang 20120809
		_pAppointView->reinit();
	}
}

void AppointMediator::updateGoldAppoint( CCNode *pNode, void *pData )
{
	if(!RoleManage::Instance()->accountInfo())
	{
		return;
	}
	int vipLev = RoleManage::Instance()->accountInfo()->_vipLev;
	int lev = RoleManage::Instance()->roleLev();
	if(_pAppointView){
		_pAppointView->updateGoldAppoint(vipLev, lev);
	}
}

void AppointMediator::startViewListener()
{
	if(!_pAppointView)
		return;

	//_pAppointView->addEventListener(AppointMediator::GOODS_DOUBLE_CLICK, this, callfuncND_selector(AppointMediator::onGoodsDoubleClick));
	_pAppointView->addEventListener(AppointMediator::APPOINT_TRADER, this, callfuncND_selector(AppointMediator::appointTrader));
	_pAppointView->addEventListener(AppointMediator::RECEIVE_ALL, this, callfuncND_selector(AppointMediator::receiveAll));
	_pAppointView->addEventListener(AppointMediator::SELL_ALL, this, callfuncND_selector(AppointMediator::sellAll));
	_pAppointView->addEventListener(AppointMediator::ON_TRADER_CLICK, this, callfuncND_selector(AppointMediator::onTraderClick));

	AccountInfoVo *pAccountInfo = RoleManage::Instance()->accountInfo();
	if(!pAccountInfo)
	{
		return ;
	}
	pAccountInfo->addEventListener(Event::CHANGE_VIPLEV, this, callfuncND_selector(AppointMediator::updateGoldAppoint));
	pAccountInfo->addEventListener(Event::CHANGE_CRYSTAL_LEV, this, callfuncND_selector(AppointMediator::updateGoldAppoint));

	AppointManager *pAppointManager = AppointManager::Instance();
	if(!pAppointManager)
	{
		return;
	}
	pAppointManager->addEventListener(AppointManager::BLESS_VALUE_CHANGE, this, callfuncND_selector(AppointMediator::blessValueChange));
	pAppointManager->addEventListener(AppointManager::BLESS_TOTAL_CHANGE, this, callfuncND_selector(AppointMediator::blessTotalChange));
}

void AppointMediator::onGoodsDoubleClick( int goodsId )
{
	BagProxy *pBagProxy = (BagProxy *) g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	if(!pBagProxy)
		return;
	int numEmpty = pBagProxy->getSpaceGridNum();
	if(numEmpty < 1)
	{
		LangManager::msgShow("APT008");
		return;
	}

	CCMD1E4 *pPacket = new CCMD1E4();
	pPacket->a_goods.push_back(goodsId);
	GameServerSocket::getInstance()->sendMessage(pPacket);
	CC_SAFE_DELETE(pPacket);
}

void AppointMediator::appointTrader( CCNode *pNode, void *pData )
{
	if(!pData)
	{
		return;
	}

	CDManage *cdManager = CDManage::Instance();
	int lock = cdManager->getLockBytype(CDManage::APPOINT);
	AppointVo *vo = (AppointVo *) pData;
	if(!vo)
	{
		return;
	}

	AccountInfoVo *pAccountInfo = RoleManage::Instance()->accountInfo();
	if(!pAccountInfo)
	{
		return;
	}
	int lev = RoleManage::Instance()->roleLev();

	if(vo->type == 1 && lev < 45)
	{
		LangManager::msgShow("APT002");
		return;
	}
	if(!vo->isGoldAppoint && lock==1)
	{	//CD��
		LangManager::msgShow("APT003");
		return;
	}
	else if(AppointManager::Instance()->_goodsArr.size() >= 12)
	{ 
		LangManager::msgShow("APT004");
		return;
	}
	if(!vo->isGoldAppoint && vo->freeNum < 1)
	{
		int ownedSilver = pAccountInfo->_silver;
		if(ownedSilver < vo->silver) 
		{
			LangManager::msgShow("APT005");
			return;
		}
	}
	if(vo->isGoldAppoint)
	{	
		//����ǽ���Ա�
		int ownedGold = pAccountInfo->_gold;
		if(ownedGold < vo->gold) 
		{
			LangManager::msgShow("APT006");
			return;
		}
		if(vo->level >= 3) return;	//��ߵȼ����˲���ʹ�ý���Ա�
	}
	CCMD1E2 *pPacket = new CCMD1E2();
	pPacket->a_type = vo->type;
	pPacket->b_lev = vo->level;
	pPacket->c_isGold = vo->isGoldAppoint;
	GameServerSocket::getInstance()->sendMessage(pPacket);
	CC_SAFE_DELETE(pPacket);
}

void AppointMediator::sellAll( CCNode *pNode, void *pData )
{
	CCMD1E5 *pPacket = new CCMD1E5();
	std::list<GoodsView *> &goodsViewList = AppointManager::Instance()->_goodsArr;
	std::list<GoodsView *>::iterator it;
	for(it = goodsViewList.begin(); it != goodsViewList.end(); ++it)
	{
		GoodsView *pGoodsView = (GoodsView *) *it;
		if(!pGoodsView || !pGoodsView->goodsVo)
		{
			continue;
		}

		pPacket->a_goods.push_back(pGoodsView->goodsVo->id);
	}
	GameServerSocket::getInstance()->sendMessage(pPacket);
	CC_SAFE_DELETE(pPacket);

	for(it = goodsViewList.begin(); it != goodsViewList.end(); ++it)
	{
		GoodsView *pGoodsView = (GoodsView *) *it;
		if(!pGoodsView || !pGoodsView->goodsVo)
		{
			continue;
		}

		//Doyang 20120810
		if(pGoodsView->getParent())
		{
			pGoodsView->removeFromParentAndCleanup(true);
		}
		pGoodsView->release();
	}
	AppointManager::Instance()->_goodsArr.clear();
}

void AppointMediator::onTraderClick( CCNode *pNode, void *pData )
{
	if(!pData || !_pAppointView)
	{
		return;
	}
	int index = *(int *) pData - 1;
	int type = (index > 3 ? 0 : 1);
	int lev = (index > 3 ? index-5 : index);
	AppointVo *newVo = AppointManager::Instance()->getTraderVoByLev(type, lev);

	newVo->freeNum = (_pAppointView->_curTraderInfo == NULL ) ? 
		0 : _pAppointView->_curTraderInfo->freeNum;
	newVo->bitNum = -1;
	_pAppointView->setCurTraderInfo(newVo);
}

void AppointMediator::blessValueChange( CCNode *pNode, void *pData )
{
	AppointManager *pAppointManager = AppointManager::Instance();
	if(!pAppointManager)
	{
		return;
	}
	if(_pAppointView && 
		_pAppointView->getisPop() &&
		ViewManager::getInstance()->mainNavigate)
	{
		_pAppointView->updateBlessInfo(ViewManager::getInstance()->mainNavigate->_isCrystalOpen,
			pAppointManager->getBlessValue(),
			pAppointManager->getBlessTotal());
	}
	/*if(_appointBlessView && _appointBlessView.isPop){
	_appointBlessView.updateExchangeState(_appointManager.blessValue);
	}*/
}

void AppointMediator::blessTotalChange( CCNode *pNode, void *pData )
{
	AppointManager *pAppointManager = AppointManager::Instance();
	if(!pAppointManager)
	{
		return;
	}
	if(_pAppointView &&
		_pAppointView->getisPop() &&
		ViewManager::getInstance()->mainNavigate)
	{
		_pAppointView->updateBlessInfo(ViewManager::getInstance()->mainNavigate->_isCrystalOpen,
			pAppointManager->getBlessValue(),
			pAppointManager->getBlessTotal());
	}
}

void AppointMediator::receiveAll( CCNode *pNode, void *pData )
{
	BagProxy *pBagProxy = (BagProxy *) g_pFacade->retrieveProxy(AppFacade_BAG_PROXY_CHANGE);
	if(!pBagProxy)
		return;
	AppointManager *pAppointManager = AppointManager::Instance();
	std::list<GoodsView *> &goodsList = pAppointManager->_goodsArr;
	int numEmpty = pBagProxy->getSpaceGridNum();
	if(numEmpty < goodsList.size())
	{
		LangManager::msgShow("APT008");
		return;
	}

	CCMD1E4 *pPacket = new CCMD1E4();
	int num = (numEmpty < goodsList.size()) ? numEmpty : goodsList.size();
	std::list<GoodsView *>::iterator it;
	for(it = goodsList.begin(); it != goodsList.end(); ++ it)
	{
		GoodsView *pGoodsView = (GoodsView *) *it;
		if(!pGoodsView || !pGoodsView->goodsVo)
			continue;

		pPacket->a_goods.push_back(pGoodsView->goodsVo->id);
	}
	GameServerSocket::getInstance()->sendMessage(pPacket);
	CC_SAFE_DELETE(pPacket);
}

void AppointMediator::exchangeHandler( CCNode *pNode, void *pData )
{
	if(!pData)
		return;

	int goodsId = *(int *) pData;

	CCMD1DC *pPacket = new CCMD1DC();
	pPacket->a_goodsId = goodsId;
	GameServerSocket::getInstance()->sendMessage(pPacket);
	CC_SAFE_DELETE(pPacket);
}
