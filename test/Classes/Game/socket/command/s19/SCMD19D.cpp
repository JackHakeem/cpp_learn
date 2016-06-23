#include "SCMD19D.h"
#include "view/crystal/CrystalMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"


bool	SCMD19D::Read()
{  
	 
	 a_type=readUbyte();
	 b_id=readUshort() ;
	 c_time=readUint(); 
	return true;
}

int32 	SCMD19D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD19DHandler::Execute(this) ;
}


uint32 SCMD19DHandler::Execute(SCMD19D* pPacket)
{
	if (!pPacket) return 1;
		
	// 服务器应答CD时间
	CCLog("Crystal:Crystal CD time response received 19D");
	CrystalMediator * crystalMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	crystalMediator->crystalUpgradeCDTimeListener((char *)pPacket);

	return 0;
}