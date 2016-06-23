#include "SCMD3DF.h"


#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/formation/FormationMediator.h"
#include "view/dungeonEntrys/DungeonEntrysMediator.h"
#include "view/tower/TowerMediator.h"

bool	SCMD3DF::Read()
{
	a_errorcode = readByte();

	return true;
}

int32 	SCMD3DF::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD3DFHandler::Execute(this) ;
}


uint32 SCMD3DFHandler::Execute(SCMD3DF* pPacket)
{
	if (!pPacket) return 1;

	g_pTowerMediator->leaveTowerListener(pPacket);
	return 0;
}