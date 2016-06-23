#include "SCMD2E9.h"
#include "socket/network/GameServerSocket.h"
#include "view/silverMine/SilverMineMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"


bool	SCMD2E9::Read()
{
	a_attackId = readUint();
	b_attackName = readString();
	c_defenceId = readUint();
	d_defenceName = readString();
	e_result = readUbyte();
	f_winRow = readUint();
	g_backHome = readByte();
	h_report1 = readUint();
	i_report2 = readUint();

	return true;
}

int32 	SCMD2E9::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2E9Handler::Execute(this) ;
}


uint32 SCMD2E9Handler::Execute(SCMD2E9* pPacket)
{
	if (!pPacket) return 1;

	SilverMineMediator * pSilverMineMediator = (SilverMineMediator*)g_pFacade->retrieveMediator(AppFacade_SilverMine_PROXY_CHANGE);
	if (pSilverMineMediator)
		pSilverMineMediator->handleBattle(pPacket);
	
	return 0;
}