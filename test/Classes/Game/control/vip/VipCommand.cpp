#include "VipCommand.h"
#include "model/vip/VipProxy.h"
#include "mvc/Facade.h"
#include "../AppFacade.h"
#include "socket/command/s29/SCMD29E.h"


void VipCommand::execute( int32 command, char* data )
{
	switch(command)
	{
	case REWARD_UPDATE:
		{
			VipProxy *pVipProxy = (VipProxy *) g_pFacade->retrieveProxy(AppFacade_VIP_PROXY);
			pVipProxy->updateVipReward((SCMD29E *)data);
		}
		break;
	default:
		break;
	}
}
