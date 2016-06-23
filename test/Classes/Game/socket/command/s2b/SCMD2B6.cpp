#include "SCMD2B6.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/trader/CityTraderMediator.h"

bool SCMD2B6::Read()
{
	int cnt = readShort();
	for (int i = 0; i< cnt; i++ )
	{
		SCMD2B6Node node;
		node.a_mapId = readShort();
		node.b_price = readShort();
		node.c_npcId = readShort();

		a_cityPriceArr.push_back(node);
	}
	return true;
}


int32 	SCMD2B6::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2B6Handler::Execute(this) ;
}


uint32 SCMD2B6Handler::Execute(SCMD2B6* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	g_pCityTraderMediator->cityPriceHandler(pPacket);

	return 0;
}