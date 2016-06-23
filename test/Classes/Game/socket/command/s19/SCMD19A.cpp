#include "SCMD19A.h"
#include "view/broadcast/BroadcastMediator.h"
#include "control/AppFacade.h"

bool SCMD19A::Read()
{
	a_type = readUbyte();
	b_id = readInt();
	c_name = readString();
	d_content = readString();

	return true;
}


int32 	SCMD19A::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD19AHandler::Execute(this) ;
}


uint32 SCMD19AHandler::Execute(SCMD19A* pPacket)
{
	if (!pPacket) return 1;

 	BroadcastMediator * pBroadCastMediator = (BroadcastMediator *)g_pFacade->retrieveMediator(AppFacade_BroadCast_Mediator);
 	if (pBroadCastMediator)
 	{
 		pBroadCastMediator->sockSysBroadcastRecived(pPacket);
 	}

	return 0;
}