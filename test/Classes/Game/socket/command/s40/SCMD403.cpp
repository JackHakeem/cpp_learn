#include "SCMD403.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/egg/EggMediator.h"

bool	SCMD403::Read()
{
	a_type = readByte();

	return true;
}

int32 	SCMD403::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD403Handler::Execute(this) ;
}


uint32 SCMD403Handler::Execute(SCMD403* pPacket)
{
	if (!pPacket) return 1;
	
	EggMediator* md = (EggMediator*)g_pFacade->retrieveMediator(AppFacade_EGG_CHANGE);
	if(md)
		md->cmdPlegeHandler(pPacket);
	
	return 0;
}