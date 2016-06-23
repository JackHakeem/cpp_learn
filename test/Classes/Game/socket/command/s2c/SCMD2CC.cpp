#include "SCMD2CC.h"
#include "view/worldBoss/WorldBossMediator.h"

bool	SCMD2CC::Read()
{
	a_result = readUbyte();
	
	return true;
}

int32 	SCMD2CC::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2CCHandler::Execute(this) ;
}


uint32 SCMD2CCHandler::Execute(SCMD2CC* pPacket)
{
	if (!pPacket) return 1;

	WorldBossMediator * pMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pMediator)
	{
		pMediator->sockBoost(pPacket);
	}

	return 0;
}