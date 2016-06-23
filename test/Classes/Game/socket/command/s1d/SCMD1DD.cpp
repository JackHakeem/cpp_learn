#include "SCMD1DD.h"
#include "view/appoint/AppointMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD1DD::Read()
{
	a_blessValue = readInt();
	b_blessTotal = readInt();
	c_isShow = readByte();
	return true;
}

int32 SCMD1DD::Execute()
{
	if(!Read())
	{
		return 1;
	}

	SCMD1DDHandler::Execute(this);
}

uint32 SCMD1DDHandler::Execute( SCMD1DD* pPacket )
{
	AppointMediator *pAppointMediator = (AppointMediator *) g_pFacade->retrieveMediator(AppFacade_APPOINT_MEDIATOR);
	if(pAppointMediator)
	{
		pAppointMediator->getAppointBlessInfo(pPacket);
	}
	return 0;
}
