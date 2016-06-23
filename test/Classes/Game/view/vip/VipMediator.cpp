#include "VipMediator.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c29/CCMD29D.h"
#include "model/player/RoleManage.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "socket/command/c29/CCMD29F.h"
#include "manager/LangManager.h"
#include "model/vip/VipProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

void VipMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case TRIAL_VIP_CHANGE:
		onTrialVipChange((SCMD3C8 *) data);
		break;
		
	case UPDATE_VIP_GOLD:
		updateVipGold((int) data);
		break;

	default:
		break;
	}
}

void VipMediator::updateVipGold( int goldNum )
{
	if(_pVipView)
	{
		_pVipView->updatePlayerInfo();
	}
	/*if(_vipView && _vipView.isPop){
		_vipView.startVipFlash();
	}*/
}

void VipMediator::onTrialVipChange( SCMD3C8 *pData )
{
	if(!pData)
	{
		return;
	}

	RoleManage::Instance()->_accountInfo._trialVip = pData->a_isTrialVip;
	if(pData->a_isTrialVip == 1)
	{
		
		RoleManage::Instance()->accountInfo()->trialVip(true);

		Message::Instance()->show(ValuesUtil::Instance()->getString("VIP102") , ccc3(12 , 233 , 25) , 3);
		//				var nowTime:int = new Date().getTime()/1000;
		//var nowTime:int = CDManage.getInstance().getServerTime()/1000;
		//_distance =  param.b_endTime - nowTime;
		//TimerManage.getInstance().add(1000, onTimer);

		GameServerSocket *_wSocket = GameServerSocket::getInstance();
		CCMD29D *pCCMD29D = new CCMD29D();
		_wSocket->sendMessage(pCCMD29D);
		CC_SAFE_DELETE(pCCMD29D); // LH0712LEAK
		//popHandler(NULL, NULL); // ignored by LH20121024
	}
	else
	{
		RoleManage::Instance()->accountInfo()->trialVip(false);
	}
}

void VipMediator::onLvChangeHandler( SCMD1EF *pData )
{
	AccountInfoVo *pAccountInfo = RoleManage::Instance()->accountInfo();
	if(pAccountInfo)
	{
		pAccountInfo->vipLev(pData->a_vipLV);
	}

	GameServerSocket *_wSocket = GameServerSocket::getInstance();
	CCMD29D *pCCMD29D = new CCMD29D();
	_wSocket->sendMessage(pCCMD29D);
	CC_SAFE_DELETE(pCCMD29D); // LH0712LEAK
}

void VipMediator::onGoldChangeHandler( SCMD1EE *pData )
{
	RoleManage::Instance()->_accountInfo._goldcount = pData->a_presentValue;
    
    //Doyang 20120810
    updateVipGold(0);
}

void VipMediator::popHandler(CCNode *pNode, void *data)
{
	this->onAddVip();
}

void VipMediator::onAddVip()
{
	if(!_pVipView)
	{
		_pVipView = new VipView();
		_pVipView->addEventListener(VipMediator::GET_VIP_REWARD, this, callfuncND_selector(VipMediator::getVipReward));
	}
	_pVipView->openVipView();
}

VipMediator::VipMediator()
{
	_pVipView = 0;
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_VIP,
		this,
		callfuncND_selector(VipMediator::popHandler));
}

void VipMediator::getVipReward( CCNode *pNode, void *pData )
{
	AccountInfoVo *pAccountInfo = RoleManage::Instance()->accountInfo();
	if(pAccountInfo &&
		pAccountInfo->vipLev() == 0 &&
		pAccountInfo->trialVip() == false)
	{
		LangManager::msgShow("VIP074");
	}
	else
	{
		CCMD29F *pPacket = new CCMD29F();
		GameServerSocket::getInstance()->sendMessage(pPacket);
		CC_SAFE_DELETE(pPacket);
		/*VipProxy *pVipProxy = (VipProxy *)g_pFacade->retrieveProxy(AppFacade_VIP_PROXY);

		if(pVipProxy && pVipProxy->getGoldReward() == 0)
		{
			LangManager::msgShow("VIP075");
		}
		else
		{
            pVipProxy->setGoldReward(0);
			CCMD29F *pPacket = new CCMD29F();
			GameServerSocket::getInstance()->sendMessage(pPacket);
			CC_SAFE_DELETE(pPacket);
		}*/
	}
}

