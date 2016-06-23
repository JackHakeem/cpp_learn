#include "SCMD1E3.h"
#include "view/appoint/AppointMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD1E3::Read()
{
	a_freeNum = readByte();
	a_goodsId = readShort();
	b_traderType = readByte();
	c_trader = readByte();
	d_selected = readByte();
	return true;
}

int32 SCMD1E3::Execute()
{
	if(!Read())
	{
		return 1;
	}

	return SCMD1E3Handler::Execute(this);
}

uint32 SCMD1E3Handler::Execute( SCMD1E3* pPacket )
{
	AppointMediator *pAppointMediator = (AppointMediator *) g_pFacade->retrieveMediator(AppFacade_APPOINT_MEDIATOR);
	if(pAppointMediator)
	{
		pAppointMediator->getAppointResult(pPacket);
	}
	return 0;
}
