#include "SCMD0F2.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"

bool	SCMD0F2::Read()
{
	int16 cnt = readShort();
	for(int16 i = 0; i < cnt; ++i)
	{
		SCMD0F2Node node;
		node.a_AccountId = readInt();
		a_Accounts.push_back(node);
	}

	return true;
}

int32 	SCMD0F2::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD0F2Handler::Execute(this) ;
}


uint32 SCMD0F2Handler::Execute(SCMD0F2* pPacket)
{
	if (!pPacket) return 1;

	SceneListenerMediator* md = 
		(SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	md->tradeplayerViewOutHandler(pPacket);

	return 0;
}