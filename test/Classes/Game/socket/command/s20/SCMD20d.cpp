#include "SCMD20d.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/friend/FriendListenerMediator.h"
#include "control/AppFacade.h"

bool	SCMD20d::Read()
{
	a_ID = readInt();
	b_delName = readString();

	return true;
}

int32 	SCMD20d::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD20dHandler::Execute(this) ;
}


uint32 SCMD20dHandler::Execute(SCMD20d* pPacket)
{
	if (!pPacket) return 1;

	
	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveMBSuccess(pPacket);
	return 0;
}