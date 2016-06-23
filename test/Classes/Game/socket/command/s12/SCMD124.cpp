#include "SCMD124.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"
bool	SCMD124::Read()
{
	int16 cnt = readShort();
	for(int16 i = 0; i < cnt; ++i)
	{
		SCMD124Node node;
		node.a_mapId = readShort();
		node.b_status = readByte();
		a_openMap.push_back(node);
	}
	
	return true;
}

int32 	SCMD124::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD124Handler::Execute(this) ;
}


uint32 SCMD124Handler::Execute(SCMD124* pPacket)
{
	if (!pPacket) return 1;
	
	SceneListenerMediator* _mediator = (SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);
	if(_mediator)
		_mediator->worldProcess(pPacket);
	return 0;
}