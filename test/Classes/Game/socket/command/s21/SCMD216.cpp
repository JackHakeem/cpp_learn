#include "SCMD216.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/friend/FriendListenerMediator.h"

bool	SCMD216::Read()
{
	a_ID = readInt();
	b_name = readString();
	c_hiredID = readShort();
	d_mainLev = readByte();

	return true;
}

int32 	SCMD216::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD216Handler::Execute(this) ;
}


uint32 SCMD216Handler::Execute(SCMD216* pPacket)
{
	if (!pPacket) return 1;

	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveAddFriendRQ(pPacket);
	
	return 0;
}