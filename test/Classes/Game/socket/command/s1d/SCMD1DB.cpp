#include "SCMD1DB.h"
#include "view/appoint/AppointMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD1DB::Read()
{
	a_id = readShort();
	b_type = readByte();
	return true;
}

int32 SCMD1DB::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD1DBHandler::Execute(this);
}

uint32 SCMD1DBHandler::Execute( SCMD1DB* pPacket )
{
	AppointMediator *pAppointMediator = (AppointMediator *) g_pFacade->retrieveMediator(AppFacade_APPOINT_MEDIATOR);
	if(pAppointMediator)
	{
		pAppointMediator->getExchangeResult(pPacket);
	}
	return 0;
}
