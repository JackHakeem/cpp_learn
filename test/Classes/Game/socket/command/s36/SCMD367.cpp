#include "SCMD367.h"
#include "view/silverMine/SilverMineMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD367::Read()
{
	short SCMD367NodeNum = readShort();
	for (short i = 0; i < SCMD367NodeNum; i++)
	{
		SCMD367Node node;
		node.a_rank = readUbyte();
		node.b_playerId = readUint();
		node.c_playerName = readString();
		node.d_silver = readUint();

		a_ranks.push_back(node);
	}
	return true;
}

int32 	SCMD367::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD367Handler::Execute(this) ;
}


uint32 SCMD367Handler::Execute(SCMD367* pPacket)
{
	if (!pPacket) return 1;

	SilverMineMediator * pSilverMineMediator = (SilverMineMediator*)g_pFacade->retrieveMediator(AppFacade_SilverMine_PROXY_CHANGE);
	if (pSilverMineMediator)
		pSilverMineMediator->handleRank(pPacket);
	return 0;
}