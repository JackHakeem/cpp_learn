#include "SCMD407.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/egg/EggMediator.h"

bool	SCMD407::Read()
{
	a_type = readByte();

	return true;
}

int32 	SCMD407::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD407Handler::Execute(this) ;
}


uint32 SCMD407Handler::Execute(SCMD407* pPacket)
{
	if (!pPacket) return 1;
	
	EggMediator* md = (EggMediator*)g_pFacade->retrieveMediator(AppFacade_EGG_CHANGE);
	if(md)
		md->cmdPickHandler(pPacket);
	
	return 0;
}