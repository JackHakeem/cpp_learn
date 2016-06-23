#include "SCMD300.h"
#include "socket/network/GameServerSocket.h"
#include "view/recruit/RecruitMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"
bool	SCMD300::Read()
{
	count = readShort();
	a_mercenarys.clear();
	int16 id = 0;
	for(int i = 0; i < count; ++i)
	{
		id = readShort();
		a_mercenarys.push_back(id);
	}

	return true;
}

int32 	SCMD300::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD300Handler::Execute(this) ;
}


uint32 SCMD300Handler::Execute(SCMD300* pPacket)
{
	if (!pPacket) return 1;	

	RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
	if ( pRecruitMediator )
	{
		pRecruitMediator->rookieListListener( pPacket );
	}

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}