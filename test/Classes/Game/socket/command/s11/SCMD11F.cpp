#include "SCMD11F.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"
#include "mvc/Facade.h"
#include "view/battle/SceneFightMediator.h"
bool	SCMD11F::Read()
{

	a_type = readUbyte();
	b_id = readUshort();

	return true;
}

int32 	SCMD11F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD11FHandler::Execute(this) ;
}


uint32 SCMD11FHandler::Execute(SCMD11F* pPacket)
{
	if (!pPacket) return 1;

// 	SceneListenerMediator* pSceneLsnMediator = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
// 	if(pSceneLsnMediator)
// 	{
// 		pSceneLsnMediator->gotoScene(pPacket->a_type,pPacket->b_id);
// 	}

	SceneFightMediator* pSceneFightMediator = (SceneFightMediator*)g_pFacade->retrieveMediator(AppFacade_FIGHT_PROXY_CHANGE);
	if(pSceneFightMediator)
	{
		pSceneFightMediator->addFollowProcess((char *)pPacket);
	}

	return 0;
}