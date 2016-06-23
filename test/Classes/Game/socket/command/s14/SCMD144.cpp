#include "SCMD144.h"
#include "socket/network/GameServerSocket.h"
#include "view/battle/SceneFightMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/honor/HonorMediator.h"

bool	SCMD144::Read()
{

	a_honorid = readShort();
	b_sucess = readByte();

	return true;
}

int32 	SCMD144::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD144Handler::Execute(this) ;
}


uint32 SCMD144Handler::Execute(SCMD144* pPacket)
{
	if (!pPacket) return 1;

	if ( g_pHonorMediator )
	{
		g_pHonorMediator->socketHonorhasGetItem( pPacket );
	}

	return 0;
}