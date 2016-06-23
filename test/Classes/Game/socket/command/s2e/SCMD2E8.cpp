#include "SCMD2E8.h"
#include "socket/network/GameServerSocket.h"
#include "view/silverMine/SilverMineMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD2E8::Read()
{
	a_mineId = readUint();
	b_moveRet = readUbyte();
	c_actionCD = readUint();
	d_inCD= readUbyte();
	e_digCD = readUint();
	f_inDigCD = readUbyte();
	h_online = readUint();
	
	return true;
}

int32 	SCMD2E8::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2E8Handler::Execute(this) ;
}


uint32 SCMD2E8Handler::Execute(SCMD2E8* pPacket)
{
	if (!pPacket) return 1;

	SilverMineMediator * pSilverMineMediator = (SilverMineMediator*)g_pFacade->retrieveMediator(AppFacade_SilverMine_PROXY_CHANGE);
	if (pSilverMineMediator)
		pSilverMineMediator->handleMoveRes(pPacket);

	return 0;
}