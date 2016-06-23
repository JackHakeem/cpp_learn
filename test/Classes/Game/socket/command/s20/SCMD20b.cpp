#include "SCMD20b.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/friend/FriendListenerMediator.h"
#include "control/AppFacade.h"

bool	SCMD20b::Read()
{
	a_ID = readInt();
	b_delName = readString();

	return true;
}

int32 	SCMD20b::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD20bHandler::Execute(this) ;
}


uint32 SCMD20bHandler::Execute(SCMD20b* pPacket)
{
	if (!pPacket) return 1;

	
	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveDFSuccess(pPacket);
	return 0;
}