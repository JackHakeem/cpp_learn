#include "SCMD2D5.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2D5::Read()
{
	a_add = readInt();
	b_num = readInt();

	return true;
}

int32 SCMD2D5::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2D5Handler::Execute(this) ;
}

uint32 SCMD2D5Handler::Execute(SCMD2D5* pPacket)
{
	if (!pPacket) return 1;
	
	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
		mUImediator->updateStoneHandler(pPacket);
	return 0;
}