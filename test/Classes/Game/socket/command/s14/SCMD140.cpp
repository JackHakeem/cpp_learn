#include "SCMD140.h"
#include "socket/network/GameServerSocket.h"
#include "view/battle/SceneFightMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/honor/HonorMediator.h"

bool	SCMD140::Read()
{

	a_honorid = readShort();

	return true;
}

int32 	SCMD140::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD140Handler::Execute(this) ;
}


uint32 SCMD140Handler::Execute(SCMD140* pPacket)
{
	if (!pPacket) return 1;

	if ( g_pHonorMediator )
		g_pHonorMediator->socketHonorHasReach( pPacket );

	return 0;
}