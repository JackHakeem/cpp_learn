#include "SCMD188.h"
#include "view/mainUI/MainUIMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD188::Read()
{
	a_presentEnergy = readInt();
	b_differance = readInt();
	c_remainVigourBuffCount = readByte();
	d_maxVigourBuffCount = readByte();
	return true;
}


int32 	SCMD188::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD188Handler::Execute(this) ;
}


uint32 SCMD188Handler::Execute(SCMD188* pPacket)
{
	if (!pPacket) return 1;

	//add code here
	CCLog("Energy change response received SCMD188");
	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator(AppFacade_MainUIMediator);
	mUImediator->updateEnergy((char *)pPacket);

	return 0;
}