#include "SCMD113.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"
bool	SCMD113::Read()
{
	int16 cnt = readShort();
	for(int16 i = 0; i < cnt; ++i)
	{
		SCMD113Node node;
		node.a_AccountId = readInt();
		a_Accounts.push_back(node);
	}
	
	return true;
}

int32 	SCMD113::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD113Handler::Execute(this) ;
}


uint32 SCMD113Handler::Execute(SCMD113* pPacket)
{
	if (!pPacket) return 1;
	
	SceneListenerMediator* md = 
		(SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->playerViewOutHandler(pPacket);

	return 0;
}