#include "SCMD21F.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/mainUI/MainUIMediator.h"

bool	SCMD21F::Read()
{
	a_gold = readUshort();
	b_energy = readUshort();
	return true;
}

int32 	SCMD21F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD21FHandler::Execute(this) ;
}


uint32 SCMD21FHandler::Execute(SCMD21F* pPacket)
{
	if (!pPacket) return 1;

 	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
 	mUImediator->initBuyEnergy((char *)pPacket);

	return 0;
}