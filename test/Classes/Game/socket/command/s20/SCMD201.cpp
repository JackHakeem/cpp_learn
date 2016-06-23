#include "SCMD201.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/friend/FriendListenerMediator.h"
#include "control/AppFacade.h"

bool	SCMD201::Read()
{
	a_total = readShort();
	b_page = readShort();

	int16 SCMD201NodeNum = readShort();	//动作次数 
	for(int k = 0; k < (int)SCMD201NodeNum; k++)
	{

		SCMD201Node newnode;
		newnode.a_ID		= readInt();	
		newnode.b_hiredID	= readShort();	
		newnode.c_name		= readString();	
		newnode.d_mainLev	= readByte();	
		newnode.e_offLine	= readByte();	
		newnode.f_fCrystal	= readByte();	
	

		c_nodeArr.push_back(newnode);
	}

	return true;
}

int32 	SCMD201::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD201Handler::Execute(this) ;
}


uint32 SCMD201Handler::Execute(SCMD201* pPacket)
{
	if (!pPacket) return 1;

	
	FriendListenerMediator* p = (FriendListenerMediator*)g_pFacade->retrieveMediator(AppFacade_OPEN_FRIENDS_COMMAND);
	if (p)
		p->receiveFList(pPacket);
	return 0;
}