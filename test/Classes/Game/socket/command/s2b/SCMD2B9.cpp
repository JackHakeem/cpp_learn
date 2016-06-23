#include "SCMD2B9.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/trader/CityTraderMediator.h"

bool SCMD2B9::Read()
{
	a_err = readShort();
	return true;
}


int32 	SCMD2B9::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2B9Handler::Execute(this) ;
}


uint32 SCMD2B9Handler::Execute(SCMD2B9* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	g_pCityTraderMediator->startBusiness(pPacket);

	return 0;
}