#include "SCMD219.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"

bool	SCMD219::Read()
{
	a_limit = readByte();
	b_hasBlessNum = readByte();
	c_hasBlessedNum = readByte();
	return true;
}

int32 	SCMD219::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD219Handler::Execute(this) ;
}


uint32 SCMD219Handler::Execute(SCMD219* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}