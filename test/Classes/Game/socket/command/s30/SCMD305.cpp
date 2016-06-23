#include "SCMD305.h"
#include "view/recruit/RecruitMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD305::Read()
{
	a_mercenaryId = readInt();
	b_result = readByte();
	
	return true;
}

int32 	SCMD305::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD305Handler::Execute(this) ;
}


uint32 SCMD305Handler::Execute(SCMD305* pPacket)
{
	if (!pPacket) return 1;

	RecruitMediator* pRecruitMediator = (RecruitMediator*)g_pFacade->retrieveMediator( AppFacade_RECRUIT_PROXY_CHANGE );
	if ( pRecruitMediator )
	{
		pRecruitMediator->dismissListener( pPacket );
	}
	
	return 0;
}