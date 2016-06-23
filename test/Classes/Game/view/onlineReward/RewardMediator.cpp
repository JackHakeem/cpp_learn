#include "RewardMediator.h"
#include "control/onlineReward/OnlineRewardCommand.h"
#include "socket/command/s1e/SCMD1ED.h"
#include "socket/command/c1e/CCMD1E7.h"
#include "socket/command/c1e/CCMD1E8.h"
#include "manager/ViewManager.h"
#include "manager/GlobalManage.h"
#include "manager/PopEventName.h"
#include "components/RewardListView.h"
#include "model/newhand/NewhandManager.h"

RewardMediator::RewardMediator() : _pOLRewardView(0)
{
	GameDispatcher::getInstance()->addEventListener(PopEventName::SHOW_UI_REWARD, this, callfuncND_selector(RewardMediator::popUIHandler));
}

RewardMediator::~RewardMediator()
{
	 
}

void RewardMediator::handleNotification( int M2Vcmd, char* data )
{
	switch(M2Vcmd) 
	{
	case REWARD_OL_UPDATE:
		{
			updateOLInfo(data);
		}
		break;
	case REWARD_AD_UPDATE:
		{
			updateADInfo(data);
		}
		break;
	default:
		break;
	}
}

void RewardMediator::popUIHandler(CCNode * pNode , void * data)
{
	openRewardView();
}

void RewardMediator::openRewardView()
{
	_pOLRewardView = ViewManager::getInstance()->_pOLRewardView;
	if (!_pOLRewardView)
	{
		_pOLRewardView = new OnlineRewardView();
		if (_pOLRewardView && _pOLRewardView->init())
		{
			_pOLRewardView->refreshListView();
			ViewManager::getInstance()->_pOLRewardView = _pOLRewardView;
		}
	}

	if (_pOLRewardView)
	{
		_pOLRewardView->setisPop(!_pOLRewardView->getisPop());

		if (_pOLRewardView->getisPop())
		{
			g_pGlobalManage->setCurFocusGID(LayerManager::windowLayer->getMyFocusGID());
		}
		else
		{
			g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
		}
	}
	
	getADRewardInfo();
}

void RewardMediator::sockOLInfo(char * data)
{
	sendNotification( Facade_Command , AppFacade_OnlineReward_Command , data , OnlineRewardCommand::REWARD_OL_UPDATE);
}

void RewardMediator::sockADInfo(char * data)
{
	sendNotification( Facade_Command , AppFacade_OnlineReward_Command , data , OnlineRewardCommand::REWARD_AD_UPDATE);
}

void RewardMediator::updateOLInfo(char * data)
{

}

void RewardMediator::updateADInfo(char * data)
{
	if (!data)
	{
		return;
	}

	SCMD1ED * pScmd = (SCMD1ED *)data;
	// update view
	OnlineRewardView * pRewardView = ViewManager::getInstance()->_pOLRewardView;
	if (pRewardView)
	{
		CCLayer * pContainer = (CCLayer * )pRewardView->_pContainer;
		if (pContainer)
		{
			RewardListView * pListView = (RewardListView *)pContainer->getChildByTag(OnlineRewardView::Tag_ListView);
			if (pListView)
			{
				pListView->refresh();
			}
		}		
	}

	if ((pScmd->a_presentValue & 1) || ((!pScmd->a_presentValue) && (!pScmd->b_addValue)))
	{
		NewhandManager::Instance()->_isNewAcount = false;
	}
}

void RewardMediator::getOLRewardInfo()
{

}

void RewardMediator::getADRewardInfo()
{
	CCMD1E7  cmd;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}

void RewardMediator::getOLReward()
{

}

void RewardMediator::getADReward()
{
	CCMD1E8 cmd;
	GameServerSocket * pSocket = GameServerSocket::getInstance();
	if (pSocket)
	{
		pSocket->sendMessage(&cmd);
	}
}