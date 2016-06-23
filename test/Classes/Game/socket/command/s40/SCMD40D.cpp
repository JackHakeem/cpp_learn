#include "SCMD40D.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/egg/EggMediator.h"

bool	SCMD40D::Read()
{
	a_type = readByte();

	return true;
}

int32 	SCMD40D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD40DHandler::Execute(this) ;
}


uint32 SCMD40DHandler::Execute(SCMD40D* pPacket)
{
	if (!pPacket) return 1;
	
	EggMediator* md = (EggMediator*)g_pFacade->retrieveMediator(AppFacade_EGG_CHANGE);
	if(md)
		md->cmdPickAllHandler(pPacket);
	
	return 0;
}