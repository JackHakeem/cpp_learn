#include "SCMD19B.h"
#include "view/broadcast/BroadcastMediator.h"
#include "control/AppFacade.h"

bool SCMD19B::Read()
{
	a_times = readUbyte();
	b_type = readUbyte();
	c_content = readString();

	return true;
}


int32 	SCMD19B::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD19BHandler::Execute(this) ;
}


uint32 SCMD19BHandler::Execute(SCMD19B* pPacket)
{
	if (!pPacket) return 1;

	BroadcastMediator * pBroadCastMediator = (BroadcastMediator *)g_pFacade->retrieveMediator(AppFacade_BroadCast_Mediator);
	if (pBroadCastMediator)
	{
		pBroadCastMediator->sockSysNoticeRecived(pPacket);
	}

	return 0;
}