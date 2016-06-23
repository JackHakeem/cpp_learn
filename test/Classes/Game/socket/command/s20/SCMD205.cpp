#include "SCMD205.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/friend/FriendListenerMediator.h"
#include "control/AppFacade.h"

bool	SCMD205::Read()
{
	a_total = readShort();
	b_page = readShort();

	int16 SCMD205NodeNum = readShort();	//动作次数 
	for(int k = 0; k < (int)SCMD205NodeNum; k++)
	{

		SCMD205Node newnode;
		newnode.a_ID		= readInt();	
		newnode.b_hiredID	= readShort();	
		newnode.c_name		= readString();	
		newnode.d_mainLev	= readByte();	
	

		c_nodeArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD205::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD205Handler::Execute(this) ;
}


uint32 SCMD205Handler::Execute(SCMD205* pPacket)
{
	if (!pPacket) return 1;

	
	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveRList(pPacket);
	return 0;
}