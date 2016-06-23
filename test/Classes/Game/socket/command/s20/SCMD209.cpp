#include "SCMD209.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/friend/FriendListenerMediator.h"
#include "control/AppFacade.h"

bool	SCMD209::Read()
{

	a_ID = readInt();
	b_name = readString();
	return true;
}

int32 	SCMD209::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD209Handler::Execute(this) ;
}


uint32 SCMD209Handler::Execute(SCMD209* pPacket)
{
	if (!pPacket) return 1;
	
	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveRQSuccess(pPacket);
	return 0;
}