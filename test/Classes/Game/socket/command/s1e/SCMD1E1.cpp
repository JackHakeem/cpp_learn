#include "SCMD1E1.h"
#include "view/appoint/AppointMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD1E1::Read()
{
	a_freeNum = readByte();
	b_ringTrader = readByte();
	c_cloakTrader = readByte();
	int16 count = readShort();
	d_goods.clear();
	for(int16 i=0; i<count; ++i)
	{
		int16 tmp = readShort();
		d_goods.push_back(tmp);
	}
	return true;
}

int32 SCMD1E1::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD1E1Handler::Execute(this);
}

uint32 SCMD1E1Handler::Execute( SCMD1E1* pPacket )
{
	AppointMediator *pAppointMediator = (AppointMediator *) g_pFacade->retrieveMediator(AppFacade_APPOINT_MEDIATOR);
	if(pAppointMediator)
	{
		pAppointMediator->getAppointInfo(pPacket);
	}
	return 0;
}
