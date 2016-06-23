#include "SCMD207.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/friend/FriendListenerMediator.h"
#include "control/AppFacade.h"

bool	SCMD207::Read()
{
	a_total = readShort();
	b_page = readShort();

	int16 SCMD207NodeNum = readShort();	//动作次数 
	for(int k = 0; k < (int)SCMD207NodeNum; k++)
	{

		SCMD207Node newnode;
		newnode.a_ID		= readInt();	
		newnode.b_name		= readString();	
		newnode.c_mainLev	= readByte();	
		newnode.d_hiredID	= readShort();	
		newnode.f_offLine	= readByte();	
	

		c_nodeArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD207::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD207Handler::Execute(this) ;
}


uint32 SCMD207Handler::Execute(SCMD207* pPacket)
{
	if (!pPacket) return 1;
	
	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveBList(pPacket);
	return 0;
}