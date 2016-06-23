#include "SCMD18A.h"
#include "view/crystal/CrystalMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/figure/FigureMediator.h"
#include "manager/GlobalManage.h"


bool	SCMD18A::Read()
{  
	a_items.clear();
    int16 len = readUshort();
	for(int i=0;i<len; i++)
	{
		SCMD18ANode node18a;
		node18a.a_id=readUbyte();
		node18a.b_level=readUbyte();
		a_items.push_back(node18a);
	}
	
	// Saved to the proxy

	return true;
}

int32 SCMD18A::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD18AHandler::Execute(this) ;
}


uint32 SCMD18AHandler::Execute(SCMD18A * pPacket)
{
	if (!pPacket) return 1;
	
	// response  : all crystal info
	CCLog("Crystal:Crystal info received 18A");
	CrystalMediator * crystalMediator = (CrystalMediator *)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	crystalMediator->crystalInfoListener((char *)pPacket);
 
	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}