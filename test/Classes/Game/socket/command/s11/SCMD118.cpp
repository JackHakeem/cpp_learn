#include "SCMD118.h"
#include "socket/network/GameServerSocket.h"
#include "view/scene/SceneListenerMediator.h"
#include "utils/Timer.h"
bool	SCMD118::Read()
{

	a_mapId = readShort();
	b_startX = readShort();
	c_startY = readShort();

	return true;
}

int32 	SCMD118::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD118Handler::Execute(this) ;
}


uint32 SCMD118Handler::Execute(SCMD118* pPacket)
{
	if (!pPacket) return 1;
	CCLog("-------------------get 118: %d",  Timer::millisecondNow());
	SceneListenerMediator* md = 
		(SceneListenerMediator*)g_pFacade->retrieveMediator(AppFacade_SCENELISTENER_MEDIATOR);

	if(md)
		md->roleMapSkip(pPacket);
	CCLog("-------------------finished 118: %d",  Timer::millisecondNow());
	return 0;
}