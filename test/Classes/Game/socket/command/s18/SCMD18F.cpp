#include "SCMD18F.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD18F::Read()
{
	a_newvalue = readInt();
	b_diffvalue = readInt();
	c_isShow = readUbyte();

	return true;
}


int32 	SCMD18F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD18FHandler::Execute(this) ;
}


uint32 SCMD18FHandler::Execute(SCMD18F* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	CCLog("Practice change response received SCMD18F");
 	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
 	mUImediator->updatePopularityHandler((char *)pPacket);

	return 0;
}