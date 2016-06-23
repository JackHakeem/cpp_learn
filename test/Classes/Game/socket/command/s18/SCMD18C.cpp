#include "SCMD18C.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD18C::Read()
{
	a_newvalue = readInt();
	b_diffvalue = readInt();
	c_isShow = readUbyte();

	return true;
}


int32 	SCMD18C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD18CHandler::Execute(this) ;
}


uint32 SCMD18CHandler::Execute(SCMD18C* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	CCLog("Sliver change response received SCMD18C");
 	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
 	mUImediator->updateSliverHandler((char*)pPacket);

	return 0;
}