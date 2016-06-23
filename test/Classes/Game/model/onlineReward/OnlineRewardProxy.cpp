#include "OnlineRewardProxy.h"
#include "view/onlineReward/RewardMediator.h"
#include "socket/command/s1e/SCMD1ED.h"
#include "OnlineRewardManager.h"
#include "manager/ViewManager.h"

OnlineRewardProxy::OnlineRewardProxy() : _presentValue(0) , _addValue(0)
{
	_goodsArray.clear();
}

OnlineRewardProxy::~OnlineRewardProxy()
{

}

void OnlineRewardProxy::updateOLInfo(char * data)
{
	if (!data)
	{
		return;
	}
	sendNotification(Facade_Mediator , AppFacade_OnlineReward_Mediator , data , RewardMediator::REWARD_OL_UPDATE);
}

void OnlineRewardProxy::updateADInfo(char * data)
{
	if (!data)
	{
		return;
	}
	SCMD1ED * pScmd = (SCMD1ED *)data;

	_presentValue = pScmd->a_presentValue;
	_addValue = pScmd->b_addValue;
	_goodsArray.assign(pScmd->c_goodsArray.begin() , pScmd->c_goodsArray.end());

	int maxSize = OnlineRewardManager::Instance()->getSize();
	if (_addValue > maxSize || (_addValue == 0) )
	{
		return;
	}
	else
	{
		if (ViewManager::getInstance()->_secNavigate)
		{
			ViewManager::getInstance()->_secNavigate->addButton(SecNavigate::TAG_LOGIN_REWARD , -1, false);		
		}
	}

	sendNotification(Facade_Mediator , AppFacade_OnlineReward_Mediator , data , RewardMediator::REWARD_AD_UPDATE);
}