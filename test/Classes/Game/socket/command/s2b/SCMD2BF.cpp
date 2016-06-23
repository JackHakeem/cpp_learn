#include "SCMD2BF.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/trader/CityTraderMediator.h"

bool SCMD2BF::Read()
{
	a_playerId = readInt();
	b_goodsNum = readShort();
	c_totalNum = readShort();
	d__robOrNot = readByte();
	e_energyCost = readShort();

	return true;
}


int32 	SCMD2BF::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2BFHandler::Execute(this) ;
}


uint32 SCMD2BFHandler::Execute(SCMD2BF* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	if (g_pCityTraderMediator)
	{
		g_pCityTraderMediator->robInfoPop(pPacket);
	}

	return 0;
}