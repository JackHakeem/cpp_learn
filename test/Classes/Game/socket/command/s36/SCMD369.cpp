#include "SCMD369.h"
#include "view/silverMine/SilverMineMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool	SCMD369::Read()
{
	a_type = readUbyte();
	b_ret = readUbyte();
	c_attPlus = readUint();
	d_defPlus = readUint();
	return true;
}

int32 	SCMD369::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD369Handler::Execute(this) ;
}


uint32 SCMD369Handler::Execute(SCMD369* pPacket)
{
	if (!pPacket) return 1;

	SilverMineMediator * pSilverMineMediator = (SilverMineMediator*)g_pFacade->retrieveMediator(AppFacade_SilverMine_PROXY_CHANGE);
	if (pSilverMineMediator)
		pSilverMineMediator->handleInspire(pPacket);
	return 0;
}