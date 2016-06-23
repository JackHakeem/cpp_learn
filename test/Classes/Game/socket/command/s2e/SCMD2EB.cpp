#include "SCMD2EB.h"
#include "socket/network/GameServerSocket.h"
#include "view/silverMine/SilverMineMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD2EB::Read()
{
	a_result = readInt();
	b_digCD = readUint();
	c_inCD = readByte();
	d_ENCHANT_ITEM_ID = readByte();
	e_enchantNum = readByte();
	return true;
}

int32 	SCMD2EB::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2EBHandler::Execute(this) ;
}


uint32 SCMD2EBHandler::Execute(SCMD2EB* pPacket)
{
	if (!pPacket) return 1;

	SilverMineMediator * pSilverMineMediator = (SilverMineMediator*)g_pFacade->retrieveMediator(AppFacade_SilverMine_PROXY_CHANGE);
	if (pSilverMineMediator)
		pSilverMineMediator->handleDigRes(pPacket);
	
	return 0;
}