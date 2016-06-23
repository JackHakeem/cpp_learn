#include "SCMD185.h"
#include "view/crystal/CrystalMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"


bool	SCMD185::Read()
{  
	a_result=readUbyte();
	b_id=readShort();
	c_level=readUbyte();

	return true;
}

int32 	SCMD185::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD185Handler::Execute(this) ;
}


uint32 SCMD185Handler::Execute(SCMD185* pPacket)
{
	if (!pPacket) return 1;

	// crystal upgrade response 
	CCLog("Crystal:Crystal Upgrade response recieved 185");
	CrystalMediator * crystalMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	crystalMediator->crystalUpgradeListener((char *)pPacket);
	return 0;
}