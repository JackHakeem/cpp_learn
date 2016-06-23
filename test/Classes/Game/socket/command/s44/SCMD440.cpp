#include "SCMD440.h"
#include "manager/LangManager.h"
#include "view/ore/OreMediator.h"
#include "control/AppFacade.h"
#include "socket/command/c44/CCMD441.h"
#include "socket/network/GameServerSocket.h"

bool SCMD440::Read()
{
	a_flag = readUint();
	return true;
}

int32 SCMD440::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD440Handler::Execute(this);
}

uint32 SCMD440Handler::Execute( SCMD440* pPacket )
{
	/*OreMediator * pOreMediator = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
	if (pOreMediator)
	{
		pOreMediator->HandleResponse(pPacket->a_flag);
	}*/
	char str[50];
	sprintf(str, "GONGMSG0%02d", pPacket->a_flag);
	LangManager::msgShow(str);


	if (pPacket->a_flag < 3)
	{
		CCMD441 cmd;
		GameServerSocket::getInstance()->sendMessage(&cmd);
	}

	return 0;
}
