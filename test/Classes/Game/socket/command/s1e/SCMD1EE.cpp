#include "SCMD1EE.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/vip/VipMediator.h"

bool SCMD1EE::Read()
{
	a_presentValue = readInt();
	b_addValue = readInt();

	return true;
}

int32 SCMD1EE::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1EEHandler::Execute(this) ;
}


uint32 SCMD1EEHandler::Execute(SCMD1EE* pPacket)
{
	if (!pPacket) return 1;
	VipMediator *pVipMediator = (VipMediator *) g_pFacade->retrieveMediator(AppFacade_VIP_MEDIATOR);
	if(pVipMediator) 
	{
		pVipMediator->onGoldChangeHandler(pPacket);
	}
	return 0;
}