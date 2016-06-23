#include "SCMD35D.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
#include "view/figure/FigureMediator.h"
#include "view/scene/SceneListenerMediator.h"

bool	SCMD35D::Read()
{
	a_accountId = readInt();

	return true;
}

int32 	SCMD35D::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD35DHandler::Execute(this) ;
}


uint32 SCMD35DHandler::Execute(SCMD35D* pPacket)
{
	if (!pPacket) return 1;

	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->playerLevelUp(pPacket);

	return 0;
}