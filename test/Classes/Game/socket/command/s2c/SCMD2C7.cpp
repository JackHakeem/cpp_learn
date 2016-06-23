#include "SCMD2C7.h"
#include "view/worldBoss/WorldBossMediator.h"
#include "manager/GlobalManage.h"

bool	SCMD2C7::Read()
{
	a_nextTime = readUint();
	b_inTime = readUbyte();

	return true;
}

int32 	SCMD2C7::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2C7Handler::Execute(this) ;
}


uint32 SCMD2C7Handler::Execute(SCMD2C7* pPacket)
{
	if (!pPacket) return 1;

	WorldBossMediator * pMediator = (WorldBossMediator * )g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pMediator)
	{
		pMediator->sockOpenTime(pPacket);
	}

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}