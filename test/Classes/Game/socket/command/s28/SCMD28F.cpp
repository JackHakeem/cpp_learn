#include "SCMD28F.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/trader/CityTraderMediator.h"


bool SCMD28F::Read()
{
	a_sil = readInt();
	b_pop = readInt();
	c_beated = readShort();
	d_BuyTokenCnt = readByte();

	return true;
}

int32 SCMD28F::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD28FHandler::Execute(this);
}

uint32 SCMD28FHandler::Execute( SCMD28F* pPacket )
{
	g_pCityTraderMediator->updateRobInfoGet(pPacket);

	return 0;
}
