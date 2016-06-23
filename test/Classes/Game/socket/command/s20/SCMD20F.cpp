#include "SCMD20F.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/friend/FriendListenerMediator.h"
#include "control/AppFacade.h"

bool	SCMD20F::Read()
{
	a_ID = readInt();
	b_delName = readString();

	return true;
}

int32 	SCMD20F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD20FHandler::Execute(this) ;
}


uint32 SCMD20FHandler::Execute(SCMD20F* pPacket)
{
	if (!pPacket) return 1;

	
	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveDBSuccess(pPacket);
	return 0;
}