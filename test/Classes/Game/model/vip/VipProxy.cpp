#include "VipProxy.h"
#include "view/vip/VipMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"


int VipProxy::getGoldReward()
{
	return _goldReward;
}

void VipProxy::setGoldReward( int value )
{
	_goldReward = value;
}

void VipProxy::updateVipReward( SCMD29E *pData )
{
	if(pData->a_num <= 0)
	{
		_hasReward = false;
	}
	else
	{
		_hasReward = true;
		_goldReward = pData->a_num;
		sendNotification(Facade_Mediator, AppFacade_VIP_MEDIATOR ,(char *)_goldReward, VipMediator::UPDATE_VIP_GOLD);
	}
}

