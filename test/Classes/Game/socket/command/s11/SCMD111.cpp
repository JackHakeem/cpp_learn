#include "SCMD111.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"
bool	SCMD111::Read()
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

int32 	SCMD111::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD111Handler::Execute(this) ;
}


uint32 SCMD111Handler::Execute(SCMD111* pPacket)
{
	if (!pPacket) return 1;
	
	SceneListenerMediator* md = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	if(md)
		md->playerMoveHandler(pPacket);

	return 0;
}