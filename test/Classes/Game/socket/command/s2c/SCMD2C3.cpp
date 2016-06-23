#include "SCMD2C3.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "../../../view/trader/CityTraderMediator.h"

bool SCMD2C3::Read()
{
	a_id = readInt();
	b_result = readByte();

	return true;
}


int32 	SCMD2C3::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2C3Handler::Execute(this) ;
}


uint32 SCMD2C3Handler::Execute(SCMD2C3* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	g_pCityTraderMediator->robReply(pPacket);

	return 0;
}