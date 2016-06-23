#include "SCMD409.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/egg/EggMediator.h"

bool	SCMD409::Read()
{
	a_type = readByte();
	b_goodsId = readInt();
	c_num = readInt();

	return true;
}

int32 	SCMD409::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD409Handler::Execute(this) ;
}


uint32 SCMD409Handler::Execute(SCMD409* pPacket)
{
	if (!pPacket) return 1;
	
	EggMediator* md = (EggMediator*)g_pFacade->retrieveMediator(AppFacade_EGG_CHANGE);
	if(md)
		md->cmdWashHandler(pPacket);
	
	return 0;
}