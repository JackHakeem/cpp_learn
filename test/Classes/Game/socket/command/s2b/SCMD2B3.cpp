#include "SCMD2B3.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/trader/CityTraderMediator.h"

bool SCMD2B3::Read()
{
	a_buyNum = readByte();
	b_restPer = readByte();

	int cnt = readShort();
	for ( int i = 0; i < cnt; i++ )
	{
		SCMD2B3Node node;
		node.a_isActive = readByte();
		node.b_ItemId = readByte();
		c_bankArr.push_back(node);
	}

	return true;
}


int32 	SCMD2B3::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2B3Handler::Execute(this) ;
}


uint32 SCMD2B3Handler::Execute(SCMD2B3* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	if (g_pCityTraderMediator)
	{
		g_pCityTraderMediator->bankListHandler(pPacket);
	}
	return 0;
}