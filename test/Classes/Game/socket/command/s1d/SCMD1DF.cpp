#include "SCMD1DF.h"
#include "LoginManage.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD1DF::Read()
{
	a_cdType = readByte();

	return true;
}

int32 	SCMD1DF::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD1DFHandler::Execute(this) ;
}


uint32 SCMD1DFHandler::Execute(SCMD1DF* pPacket)
{
	if (!pPacket) return 1;

	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
	if (mUImediator)
		mUImediator->freeClearCDHandler(pPacket);

	return 0;
}