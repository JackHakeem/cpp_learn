#include "SCMD211.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "view/friend/FriendListenerMediator.h"


bool	SCMD211::Read()
{
	a_ID = readInt();
	b_name = readString();

	return true;
}

int32 	SCMD211::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD211Handler::Execute(this) ;
}


uint32 SCMD211Handler::Execute(SCMD211* pPacket)
{
	if (!pPacket) return 1;

	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveDBFLSuccess(pPacket);
	return 0;
}