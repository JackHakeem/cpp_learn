#include "CrystalMediator.h"
#include "control/AppFacade.h"
#include "mvc/Facade.h"
#include "control/crystal/CrystalCommand.h"
#include "manager/ViewManager.h"
#include "view/crystal/components/CrystalView.h"
#include "control/crystal/CrystalCommand.h"
#include "mvc/Facade.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c18/CCMD189.h"
#include "socket/command/s18/SCMD185.h"
#include "socket/command/s19/SCMD19D.h"
#include "Message.h"
#include "model/crystal/CrystalManager.h"
#include "utils/ValuesUtil.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "socket/command/s18/SCMD187.h"
#include "socket/command/c19/CCMD19C.h"
#include "socket/command/c18/CCMD182.h"
#include "socket/command/c19/CCMD19E.h"
#include "socket/command/s18/SCMD183.h"
#include "socket/command/s17/SCMD17F.h"
#include "manager/CDManage.h"
#include "socket/command/c2e/CCMD2E0.h"
#include "socket/command/s2e/SCMD2E1.h"
#include "../newhand/NewhandMediator.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "components/CrystalTimer.h"
#include "CustomCD.h"
#include "model/player/RoleManage.h"
#include "components/CrystalUIPartialScrollView.h"

CrystalMediator::CrystalMediator()
{
	_crystalView = ViewManager::getInstance()->crystalView;
	_crystalCommand = NULL;
	if (!_crystalCommand)
	{
		_crystalCommand = (CrystalCommand *)g_pFacade->retrieveController(AppFacade_CRYSTAL_PROXY_CHANGE);
	}
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_CRYSTAL, 
		this,
		callfuncND_selector(CrystalMediator::popHandler));
}

void CrystalMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd)
	{
	case  INIT_CRYSTAL:
		//initCrystalView();
		break;
	case  UPGRADE_CRYSTAL:
		upgradeCrystalHandler(data);
		break;
	case  UPDATE_CDTIME:
		updateCDTime(data);
		break;
	case UPDATE_CDLIST:
		updateCDList(data);
		break;
	case UPDATE_VIEW:
		updateView();
		break;
	default:
		break;
	}
}

CrystalMediator::~CrystalMediator()
{

}

void CrystalMediator::crystalInfoListener(char * data)
{
	sendNotification(Facade_Command,AppFacade_CRYSTAL_PROXY_CHANGE,data,CrystalCommand::INIT_CRYSTALS);
	// openCrystalView();
}

void CrystalMediator::crystalActivateListener(char * data)
{
	sendNotification(Facade_Command,AppFacade_CRYSTAL_PROXY_CHANGE,data,CrystalCommand::UPDATE_CRYSTALS);
}

void CrystalMediator::crystalUpgradeListener(char * data)
{
	sendNotification(Facade_Command,AppFacade_CRYSTAL_PROXY_CHANGE,data,CrystalCommand::UPGRADE_CRYSTALS);
}

void CrystalMediator::crystalUpgradeCDTimeListener(char * data)
{
	SCMD19D * cmd = (SCMD19D *)data;
	if (cmd->a_type != 3)
	{
		return;
	}	
	sendNotification(Facade_Command,AppFacade_CRYSTAL_PROXY_CHANGE,data,CrystalCommand::UPGRADE_CDTIME);
}

void CrystalMediator::crystalCDLeftTimeListener(char * data)
{
	sendNotification(Facade_Command,AppFacade_CRYSTAL_PROXY_CHANGE,data,CrystalCommand::UPGRADE_CDLIST);
}

/**
* Open the crystalline system interface
*/	
void CrystalMediator::sendCrystalInfoReq()
{
		CCMD189* s = new CCMD189();
		if (s)
		{
			GameServerSocket* pSocket = GameServerSocket::getInstance();
			if (pSocket)
			pSocket->sendMessage(s);
			cocos2d::CCLog("Crystal Info Request:CCMD189");
		}
		SAFE_DELETE(s);
}

void CrystalMediator::reqUpgradeTime(int id)
{
	CCMD19C* s = new CCMD19C();
	if (s)
	{
		s->a_type = 3;
		s->b_id = id;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(s);
		cocos2d::CCLog("Crystal CD time Request:CCMD19C");
	}
	SAFE_DELETE(s);
}

void CrystalMediator::initCrystalView()
{
	_crystalView = ViewManager::getInstance()->crystalView;
	if (!_crystalView)
	{
		_crystalView = new CrystalView();
		if(_crystalView && _crystalView->initCrystalView())
		{
			CCLog("Crystal:initCrystalView() success");
		}
		else
		{
			CCLog("Crystal:initCrystalView() failed");
			return;
		}
		ViewManager::getInstance()->crystalView = _crystalView;
	}
}

void CrystalMediator::popCrystalView()
{
	_crystalView = ViewManager::getInstance()->crystalView;
	if (!_crystalView)
	{
		_crystalView = new CrystalView();
		if(_crystalView && _crystalView->initCrystalView())
		{
			CCLog("Crystal:initCrystalView() success");
		}
		else
		{
			CCLog("Crystal:initCrystalView() failed");
			return;
		}
		ViewManager::getInstance()->crystalView = _crystalView;
	}

	_crystalView->setisPop(!_crystalView->getisPop());

	int count = RoleManage::Instance()->_accountInfo._numCrystalCd;
	int begin = CDManage::CRYSTAL_0;
	for (int i = begin;i < begin+count ; i++)
	{
		CustomCD * pCustomCD = (CustomCD *)_crystalView->_container->getChildByTag(CrystalView::TAG_CDITEM_1+i-begin);
		if (pCustomCD)
		{
			pCustomCD->reinit();
		}
	}

	// refresh left items
	_crystalView->initItemsInScrollView();

	// new hand
	if (g_pCrystalScrollView)
	{
		int index = 1;
		g_pCrystalScrollView->_nPosIndex = index;
		g_pCrystalScrollView->addHightLightFocusImage(index);
		updateDetailInfo(CRYSTALS[index]);
		reqUpgradeTime(CRYSTALS[index]);
	}
	

	if(_crystalView->getisPop())
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID()); // add by LH 0412
		// to create manager cash data
		// add code here
	}
	else
	{
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID()); // add by LH 0425
	}
}

void CrystalMediator::upgradeCrystalHandler(char * data)
{
	SCMD185 * s = (SCMD185 *)data;
	
	Message * message = Message::Instance();
	CCLog("Crystal:upgrade result code %d  %x",s->a_result,data);
	uint8 result = (uint8)s->a_result;
	short id = s->b_id;
	int lev = s->c_level;

	struct Data
	{
		int type;
		int lev;
	};

	Data * pData = new Data();
	pData->type = id;
	pData->lev = lev;

	switch (result)
	{
	case 0:
		{
			_crystalView = ViewManager::getInstance()->crystalView;
			if (_crystalView && _crystalView->getisPop())
			{
				_crystalView->showCrystalInfo(id);
				_crystalView->initItemsInScrollView();
			}
			
			//message->show(CrystalManager::Instance()->_cv->getString("CUT0"),ccc3(255,133,25),1);
			_crystalCommand->sendCDListRequest(id);

			GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::CRYSTAL_LEVEL_CHANGE, pData);
			/*
			// Call newhand.
			NewhandMediator *pNewhandMediator = (NewhandMediator *) g_pFacade->retrieveMediator(AppFacade_NEWHAND_MEDIATOR);
			TestNewhand::CrystalParam *pData = new TestNewhand::CrystalParam();
			pData->lev = l;
			pNewhandMediator->cryLevTrigger(NULL, pData);
			*/
		}
		break;
	case 1:
		//message->show(CrystalManager::Instance()->_cv->getString("CUT1"),ccc3(255,133,25),1);
		break;
	case 3:
		//message->show(CrystalManager::Instance()->_cv->getString("CUT3"),ccc3(255,133,25),1);
		break;
	case 5:
		//message->show(CrystalManager::Instance()->_cv->getString("CUT5"),ccc3(255,133,25),1);
		break;
	default:
		break;
	}
	
	CC_SAFE_DELETE(pData); // jae0813
}

// update CD time
void CrystalMediator::updateCDTime(char *data)
{
	SCMD19D* cmd=(SCMD19D*)data;
	if(!cmd) return;
	_crystalView = ViewManager::getInstance()->crystalView;
	if (_crystalView && _crystalView->getisPop())
	{
		_crystalView->showCrystalInfo(cmd->b_id);
	}
}

// update CD left time
void CrystalMediator::updateCDList(char * data)
{
	SCMD187* cmd=(SCMD187*)data;
	if(!cmd) return;
	_crystalView = ViewManager::getInstance()->crystalView;
	if (_crystalView)
	{
		//_crystalView->updateCDList(cmd->a_type,cmd->b_incd,cmd->c_time);

		_crystalView->showCDPannel(); // LH0717
	}
}

// update left panel info
void CrystalMediator::updateView()
{
	_crystalView = ViewManager::getInstance()->crystalView;
	if (_crystalView && _crystalView->getisPop())
	{
		_crystalView->initItemsInScrollView();
	}
}

// update right panel detail info
void CrystalMediator::updateDetailInfo(int id)
{
	_crystalView = ViewManager::getInstance()->crystalView;
	if (_crystalView && _crystalView->getisPop())
	{
		_crystalView->curSelectCrystalID = id;
		_crystalView->showCrystalInfo(id);
	}
}

void CrystalMediator::reqMoney(uint8 type)
{
	CCMD19E* s = new CCMD19E();
	if (s)
	{
		s->a_type = (uint8)type;
		GameServerSocket* pSocket = GameServerSocket::getInstance();
		if (pSocket)
			pSocket->sendMessage(s);
		cocos2d::CCLog("Crystal buy CD time gold needed Request:CCMD19E");
	}
	SAFE_DELETE(s);
}

void CrystalMediator::respMoney(char * pPacket)
{
	_crystalView = ViewManager::getInstance()->crystalView;
	if (!_crystalView) return;
	_crystalView->clearCD(pPacket);
}

void CrystalMediator::reqClearCD(int type,int cost)
{
	CCMD182 cmd;
	cmd.a_type = (uint8)type;
	cmd.b_free = (uint8)(!cost);
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void CrystalMediator::respClearCD(char * pPacket)
{
	SCMD183 * cmd = (SCMD183 *)pPacket;
	if (!cmd) return;

	if (cmd->a_state == 0)
	{
		_crystalView = ViewManager::getInstance()->crystalView;
		if (!_crystalView) return;
		_crystalView->showCDPannel();
		//_crystalView->updateCDList(cmd->b_type,0,0);
	}
	else if (cmd->a_state == 6)
	{
		//Message::Instance()->show(ValuesUtil::Instance()->getString("PY19"),ccc3(233,12,12),1);
		return;
	}
	else{}
}

void CrystalMediator::initCDList(char * data)
{
	SCMD17F * cmd = (SCMD17F *)data;
	std::vector<SCMD17F::SCMD17FNode> *pNode = &cmd->a_cd;
	std::vector<SCMD17F::SCMD17FNode>::iterator iter = pNode->begin();
	for (;iter != pNode->end();iter++)
	{
		if (iter->a_type < CDManage::CRYSTAL_0 || iter->a_type > CDManage::CRYSTAL_5) {continue;}
		_crystalView = ViewManager::getInstance()->crystalView;
		if (_crystalView /*&& _crystalView->getisPop()*/)
		{
			//_crystalView->updateCDList(iter->a_type,iter->b_incd,iter->c_time);
			_crystalView->showCDPannel(); // LH0717
		}		
	}
}

void CrystalMediator::sendBuyCDListReq(int type)
{
	CCMD2E0 cmd;
	cmd.a_type = (uint8)type;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
		CCLog("Crystal:Buy CD list request sent,CCMD2E1");
	}
}

void CrystalMediator::sockBuyCrystalCDList(char * data)
{
	SCMD2E1 * cmd = (SCMD2E1 *)data;

	RoleManage::Instance()->_accountInfo._numCrystalCd = cmd->b_listNum;

	_crystalView = ViewManager::getInstance()->crystalView;
	if (!_crystalView) {return;}
	_crystalView->buyCrystalCDList(cmd->a_value,cmd->b_listNum);
}

void CrystalMediator::popHandler( CCNode *pNode, void *data )
{
	this->popCrystalView();
}
