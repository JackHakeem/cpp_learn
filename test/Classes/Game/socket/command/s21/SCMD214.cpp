#include "SCMD214.h"
#include "socket/network/GameServerSocket.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"

bool	SCMD214::Read()
{
	a_flag = readByte();

	return true;
}

int32 	SCMD214::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD214Handler::Execute(this) ;
}


uint32 SCMD214Handler::Execute(SCMD214* pPacket)
{
	if (!pPacket) return 1;

	switch(pPacket->a_flag)
	{
		case 211:
			LangManager::msgShow("FRD032");
			break;
		case 212:
			LangManager::msgShow("FRD033");
			break;
		case 213:
			LangManager::msgShow("FRD034");
			break;
		case 214:
			LangManager::msgShow("FRD035");
			break;
		case 215:
			LangManager::msgShow("FRD036");
			break;
		case 216:
			LangManager::msgShow("FRD037");
			break;
		case 217:
			LangManager::msgShow("FRD038");
			break;
		case 218:
			LangManager::msgShow("FRD039");
			break;
		default:
			LangManager::msgShow("FRD040");
			break;
	}
	return 0;
}