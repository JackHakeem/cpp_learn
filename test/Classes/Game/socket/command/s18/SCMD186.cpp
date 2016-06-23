#include "SCMD186.h"
#include "mvc/Facade.h"
#include "view/crystal/CrystalMediator.h"
#include "control/AppFacade.h"


bool	SCMD186::Read()
{  
    a_result=readUbyte();
	b_id=readUbyte();
	c_level=readUbyte();

	return true;
}

int32 	SCMD186::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD186Handler::Execute(this) ;
}


uint32 SCMD186Handler::Execute(SCMD186* pPacket)
{
	if (!pPacket) return 1;

	// response: server activates a crystal 
	CCLog("Crystal:Crystal activate response received 186");
 	CrystalMediator * crystalMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
 	crystalMediator->crystalActivateListener((char *)pPacket);

	return 0;
}