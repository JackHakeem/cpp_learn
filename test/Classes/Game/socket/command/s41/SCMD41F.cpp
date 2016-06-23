#include "SCMD41F.h"
#include "manager/GlobalManage.h"
#include "utils/Timer.h"
#include "socket/command/c41/CCMD41E.h"
#include "../../network/GameServerSocket.h"

bool SCMD41F::Read()
{
	a_res = readByte();

	return true;
}

int32 SCMD41F::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD41FHandler::Execute(this) ;
}

uint32 SCMD41FHandler::Execute(SCMD41F* pPacket)
{
	if (!pPacket) return 1;
	//

	if (pPacket->a_res == 0)
	{
		int delay = Timer::millisecondNow() - g_pGlobalManage->g_netDelay;
		CCMD41E msg;
		msg.a_req = 1;
		msg.b_delay = delay / 2;
		GameServerSocket::getInstance()->sendMessage(&msg);
	}
	else if (pPacket->a_res == 1)
	{
		g_pGlobalManage->g_netDelay = Timer::millisecondNow();
		CCMD41E msg;
		msg.a_req = 0;
		GameServerSocket::getInstance()->sendMessage(&msg);
	}
	else
	{
		CCLog("SCMD41F::receive a error packet.");
	}
	return 0;
}

