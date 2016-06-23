#include "SCMD120.h"
#include "socket/network/GameServerSocket.h"
#include "view/login/LoginMediator.h"
#include "view/scene/SceneListenerMediator.h"
bool	SCMD120::Read()
{

	a_mapId = readShort();
	b_process = readShort();

	return true;
}

int32 	SCMD120::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD120Handler::Execute(this) ;
}


uint32 SCMD120Handler::Execute(SCMD120* pPacket)
{
	if (!pPacket) return 1;
	
	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->addProcess(pPacket);

	return 0;
}