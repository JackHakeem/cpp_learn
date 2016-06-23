#include "SCMD11B.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/scene/SceneListenerMediator.h"

bool	SCMD11B::Read()
{
	a_type = readByte();
	b_id = readShort();

	return true;
}

int32 	SCMD11B::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD11BHandler::Execute(this) ;
}


uint32 SCMD11BHandler::Execute(SCMD11B* pPacket)
{
	if (!pPacket) return 1;
	
	SceneListenerMediator* md = 
		(SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->roleMoveHandler(pPacket);

	return 0;
}