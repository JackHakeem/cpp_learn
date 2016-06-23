#include "SCMD2CE.h"
#include "view/worldBoss/WorldBossMediator.h"

bool	SCMD2CE::Read()
{
	a_mode = readUbyte();
	b_result = readUbyte();
	
	return true;
}

int32 	SCMD2CE::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2CEHandler::Execute(this) ;
}


uint32 SCMD2CEHandler::Execute(SCMD2CE* pPacket)
{
	if (!pPacket) return 1;

	WorldBossMediator * pMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pMediator)
	{
		pMediator->sockRelive(pPacket);
	}

	return 0;
}