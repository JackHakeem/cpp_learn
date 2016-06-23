#include "SCMD12F.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"

bool	SCMD12F::Read()
{
	a_AccountId = readInt();
	b_startX = readShort();
	c_startY = readShort();
	int16 cnt = readShort();
	for(int16 i = 0; i < cnt; ++i)
	{
		SCMD111Node node;
		node.a_x = readShort();
		node.b_y = readShort();
		d_path.push_back(node);
	}
	return true;
}

int32 	SCMD12F::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD12FHandler::Execute(this) ;
}


uint32 SCMD12FHandler::Execute(SCMD12F* pPacket)
{
	if (!pPacket) return 1;

	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	if(md)
		md->tradeplayerMoveHandler(pPacket);

	return 0;
}