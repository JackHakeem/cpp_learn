#include "SCMD2BB.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/trader/CityTraderMediator.h"

bool SCMD2BB::Read()
{
	a_err = readShort();
	b_silver = readInt();
	c_bj = readByte();
	d_pop = readInt();
	e_doubleTime = readByte();

	return true;
}


int32 	SCMD2BB::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2BBHandler::Execute(this) ;
}


uint32 SCMD2BBHandler::Execute(SCMD2BB* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	if (g_pCityTraderMediator)
		g_pCityTraderMediator->endBusiness(pPacket);

	return 0;
}