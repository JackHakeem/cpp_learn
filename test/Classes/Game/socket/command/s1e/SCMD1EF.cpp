#include "SCMD1EF.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/vip/VipMediator.h"

bool SCMD1EF::Read()
{
	a_vipLV = readByte();

	return true;
}

int32 SCMD1EF::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD1EFHandler::Execute(this) ;
}


uint32 SCMD1EFHandler::Execute(SCMD1EF* pPacket)
{
	if (!pPacket) return 1;
	VipMediator *pVipMediator = (VipMediator *) g_pFacade->retrieveMediator(AppFacade_VIP_MEDIATOR);
	if(pVipMediator) 
	{
		pVipMediator->onLvChangeHandler(pPacket);
	}
	return 0;
}