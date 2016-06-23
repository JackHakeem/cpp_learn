#include "OnlineRewardCommand.h"
#include "model/onlineReward/OnlineRewardProxy.h"

OnlineRewardCommand::OnlineRewardCommand()
{
	_pRewardProxy = (OnlineRewardProxy *)g_pFacade->retrieveProxy(AppFacade_OnlineReward_Proxy);
}

OnlineRewardCommand::~OnlineRewardCommand()
{

}

void OnlineRewardCommand::execute(int32 command, char* data)
{
	switch(command)
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

void OnlineRewardCommand::updateOLInfo(char * data)
{
	if (_pRewardProxy)
	{
		_pRewardProxy->updateOLInfo(data);
	}
}

void OnlineRewardCommand::updateADInfo(char * data)
{
	if (_pRewardProxy)
	{
		_pRewardProxy->updateADInfo(data);
	}
}