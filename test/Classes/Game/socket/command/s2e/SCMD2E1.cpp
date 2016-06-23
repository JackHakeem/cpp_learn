#include "SCMD2E1.h"
#include "socket/network/GameServerSocket.h"
#include "view/crystal/CrystalMediator.h"

bool	SCMD2E1::Read()
{
	a_value = readUbyte();
	b_listNum = readUbyte();

	return true;
}

int32 	SCMD2E1::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2E1Handler::Execute(this) ;
}


uint32 SCMD2E1Handler::Execute(SCMD2E1* pPacket)
{
	if (!pPacket) return 1;

	CCLog("Crystal:Buy CD list response received.SCMD2E1");
	CrystalMediator * pCrysMediator = (CrystalMediator*)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	if (pCrysMediator)
	{
		pCrysMediator->sockBuyCrystalCDList((char *)pPacket);
	}
	
	return 0;
}