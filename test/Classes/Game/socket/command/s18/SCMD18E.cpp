#include "SCMD18E.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD18E::Read()
{
	a_newvalue = readInt();
	b_diffvalue = readInt();
	c_isShow = readUbyte();

	return true;
}


int32 	SCMD18E::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD18EHandler::Execute(this) ;
}


uint32 SCMD18EHandler::Execute(SCMD18E* pPacket)
{
		if (!pPacket) return 1;

	//add code here
	CCLog("Practice change response received SCMD18E");
 	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
 	mUImediator->updatePracticeHandler((char *)pPacket);

	return 0;
}