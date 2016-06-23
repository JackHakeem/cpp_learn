#include "SCMD3C8.h"
#include "view/login/LoginMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"


bool SCMD3C8::Read()
{
	a_isTrialVip = readByte();
	b_endTime = readInt();
	return true;
}

int32 SCMD3C8::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD3C8Handler::Execute(this);
}

uint32 SCMD3C8Handler::Execute( SCMD3C8* pPacket )
{
	if (!pPacket)
	{
		return 1;
	}
	LoginMediator *pLoginMediator = (LoginMediator *) g_pFacade->retrieveMediator(AppFacade_LOGIN_MEDIATOR);
	if(pLoginMediator)
	{
		pLoginMediator->trialVipState(pPacket);
	}
	return 0;
}
