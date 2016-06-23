#include "SCMD1E6.h"
#include "view/appoint/AppointMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD1E6::Read()
{
	a_goodsId = readShort();
	return true;
}

int32 SCMD1E6::Execute()
{
	if(!Read())
	{
		return 1;
	}
	SCMD1E6Handler::Execute(this);
}

uint32 SCMD1E6Handler::Execute( SCMD1E6* pPacket )
{
	AppointMediator *pAppointMediator = (AppointMediator *) g_pFacade->retrieveMediator(AppFacade_APPOINT_MEDIATOR);
	if(pAppointMediator)
	{
		pAppointMediator->getAppointGoods(pPacket);
	}
	return 0;
}
