#include "SCMD213.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"

bool	SCMD213::Read()
{
	a_playerId = readInt();
	b_name = readString();
	c_avatarId = readShort();
	d_mainCyLev = readByte();

	return true;
}

int32 	SCMD213::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD213Handler::Execute(this) ;
}


uint32 SCMD213Handler::Execute(SCMD213* pPacket)
{
	if (!pPacket) return 1;


	return 0;
}