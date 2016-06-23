#include "SCMD2ED.h"
#include "socket/network/GameServerSocket.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD2ED::Read()
{
	a_time = readUint();
	b_timeGong = readUint();

	return true;
}

int32 	SCMD2ED::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2EDHandler::Execute(this) ;
}


uint32 SCMD2EDHandler::Execute(SCMD2ED* pPacket)
{
	if (!pPacket) return 1;

	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
	if (mUImediator)
		mUImediator->mineOpenTime(pPacket);

	return 0;
}