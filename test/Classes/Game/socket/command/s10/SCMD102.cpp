#include "SCMD102.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "events/GameDispatcher.h"

bool	SCMD102::Read()
{
	a_result = readByte();
	b_accountId = readUint();
	c_guild = readInt();
	d_line = readByte();
	e_ip = readString();
	f_port = readShort();
	g_key = readInt();
	h_sn = readString();

	return true;
}

int32 	SCMD102::Execute()
{
	if (!Read())
	{
		return 1;
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::GATE_SERVER_CONNECT_FAILED, NULL);
	}

	return SCMD102Handler::Execute(this) ;
}

uint32 SCMD102Handler::Execute(SCMD102* pPacket)
{
	if (!pPacket) return 1;

	if (pPacket->a_result == 1)
	{
		g_pLoginManage->gSocketLoginSucc(pPacket);
		
	}
	else if (pPacket->a_result == 2)
	{
		// need to greate a role
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::LOGIN_CREATEROLE, NULL);
	}
	else if (pPacket->a_result == 3)
	{
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::LOGIN_VERSIONERR, NULL);
	}
	else if (pPacket->a_result == 4)
	{
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::LOGIN_FORBBIDEN, NULL);
	}
	

	return 0;
}