#include "SCMD2E3.h"
#include "socket/network/GameServerSocket.h"
#include "view/silverMine/SilverMineMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD2E3::Read()
{
	a_ret = readByte();

	return true;
}

int32 	SCMD2E3::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2E3Handler::Execute(this) ;
}


uint32 SCMD2E3Handler::Execute(SCMD2E3* pPacket)
{
	if (!pPacket) return 1;

	SilverMineMediator * pSilverMineMediator = (SilverMineMediator*)g_pFacade->retrieveMediator(AppFacade_SilverMine_PROXY_CHANGE);
	if (pSilverMineMediator)
		pSilverMineMediator->handleEnterRes(pPacket);
	
	return 0;
}