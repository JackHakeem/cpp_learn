#include "SCMD18D.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD18D::Read()
{
	a_newvalue = readInt();
	b_diffvalue = readInt();
	c_isShow = readByte();

	return true;
}


int32 	SCMD18D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD18DHandler::Execute(this) ;
}


uint32 SCMD18DHandler::Execute(SCMD18D* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	CCLog("Gold change response received SCMD18D");
 	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
 	mUImediator->updateGoldHandler((char *)pPacket);

	return 0;
}