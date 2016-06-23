#include "SCMD11C.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/scene/SceneListenerMediator.h"

bool	SCMD11C::Read()
{
	a_x = readShort();
	b_y = readShort();

	return true;
}

int32 	SCMD11C::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD11CHandler::Execute(this) ;
}


uint32 SCMD11CHandler::Execute(SCMD11C* pPacket)
{
	if (!pPacket) return 1;
	
	SceneListenerMediator* md = 
		(SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->resetLocation(pPacket);

	return 0;
}