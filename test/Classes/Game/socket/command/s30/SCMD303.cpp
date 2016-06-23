#include "SCMD303.h"
#include "view/recruit/RecruitMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD303::Read()
{
	a_prototypeId = readShort();
	b_mercenaryId = readInt();
	
	return true;
}

int32 	SCMD303::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD303Handler::Execute(this) ;
}


uint32 SCMD303Handler::Execute(SCMD303* pPacket)
{
	if (!pPacket) return 1;

	RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
	if ( pRecruitMediator )
	{
		pRecruitMediator->recruitListener( pPacket );
	}
	
	return 0;
}