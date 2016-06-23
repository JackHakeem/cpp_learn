#include "SCMD2B2.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/trader/CityTraderMediator.h"

bool SCMD2B2::Read()
{
	a_item1 = readByte();
	b_refreshTimes = readShort();
	c_beated = readShort();
	d_buyTokenCnt = readShort();
	e_robSilver = readInt();
	e_robPop = readInt();
	f_mapId = readShort();

	return true;
}


int32 	SCMD2B2::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2B2Handler::Execute(this) ;
}


uint32 SCMD2B2Handler::Execute(SCMD2B2* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	g_pCityTraderMediator->goodsListHandler(pPacket);

	return 0;
}