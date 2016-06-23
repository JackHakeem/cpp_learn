#include "SCMD405.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/egg/EggMediator.h"

bool	SCMD405::Read()
{
	a_type = readByte();
	b_eggId = readInt();
	c_goodsId = readInt();
	d_goodsNum = readInt();

	return true;
}

int32 	SCMD405::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD405Handler::Execute(this) ;
}


uint32 SCMD405Handler::Execute(SCMD405* pPacket)
{
	if (!pPacket) return 1;
	
	EggMediator* md = (EggMediator*)g_pFacade->retrieveMediator(AppFacade_EGG_CHANGE);
	if(md)
		md->cmdOpenHandler(pPacket);
	
	return 0;
}