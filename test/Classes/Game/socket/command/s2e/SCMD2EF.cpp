#include "SCMD2EF.h"
#include "socket/network/GameServerSocket.h"
//#include "view/crystal/CrystalMediator.h"

bool	SCMD2EF::Read()
{
	a_type = readUbyte();
	b_mineID = readUint();
	c_ret = readUbyte();
	d_param = readUint();

	return true;
}

int32 	SCMD2EF::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD2EFHandler::Execute(this) ;
}


uint32 SCMD2EFHandler::Execute(SCMD2EF* pPacket)
{
	if (!pPacket) return 1;

	//CCLog("Crystal:Buy CD list response received.SCMD2EF");
	//CrystalMediator * pCrysMediator = (CrystalMediator*)g_pFacade->retrieveMediator(AppFacade_CRYSTAL_PROXY_CHANGE);
	//if (pCrysMediator)
	//{
	//	pCrysMediator->sockBuyCrystalCDList((char *)pPacket);
	//}
	
	return 0;
}