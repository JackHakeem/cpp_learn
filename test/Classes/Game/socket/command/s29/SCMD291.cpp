#include "SCMD291.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "mvc/Facade.h"
#include "view/recruit/RecruitMediator.h"
#include "control/AppFacade.h"

bool	SCMD291::Read()
{
	a_mercLim = readByte();

	return true;
}

int32 	SCMD291::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD291Handler::Execute(this) ;
}


uint32 SCMD291Handler::Execute(SCMD291* pPacket)
{
	if (!pPacket) return 1;

	RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
	if ( !pRecruitMediator )
	{
		pRecruitMediator->mercLimListener( pPacket );
	}

	return 0;
}